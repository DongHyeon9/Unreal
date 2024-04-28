// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UObject/UnrealTypePrivate.h"
#include "JSGameInstance.generated.h"

class IHttpRequest;
class IHttpResponse;

typedef TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> FHttpRequestPtr;
typedef TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> FHttpResponsePtr;

UENUM(BlueprintType)
enum class ECHARACTER_CLASS : uint8 {
	WARRIOR			UMETA(DisplayName = "Warrior"),
	MAGE			UMETA(DisplayName = "Mage"),
	ARCHER			UMETA(DisplayName = "Archer"),
	ASSASSIN		UMETA(DisplayName = "Assassin"),
};

USTRUCT(Atomic, BlueprintType)
struct FSkillData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "SkillData")
	FString skillName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "SkillData")
	int32 skillLevel;

	FSkillData() :
		skillName(TEXT("None")),
		skillLevel() {}

	FSkillData(FString _Name, int32 _Level) :
		skillName(_Name),
		skillLevel(_Level) {}
};


USTRUCT(Atomic, BlueprintType)
struct FPlayerData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString userName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECHARACTER_CLASS characterClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Status")
	int32 level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Status")
	int32 damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Status")
	int32 armor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Skill")
	TArray<FSkillData> skilldata;

	FPlayerData() :
		userName(TEXT("NiceNews")),
		characterClass(ECHARACTER_CLASS::MAGE),
		level(1),
		damage(100),
		armor(30),
		skilldata() {
		skilldata.Reserve(3);
		skilldata.Emplace(TEXT("FireBall"), 1);
		skilldata.Emplace(TEXT("IceBall"), 2);
		skilldata.Emplace(TEXT("WaterBall"), 3);
	}
};

/**
 *
 */
UCLASS()
class JSONPRJ_API UJSGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:

protected:

private:

public:
	UJSGameInstance();

protected:
	virtual void Init()override;

	void PostJson(FString _Json, FString _IP);

	bool SaveJsonToFile(FString _Json, FString _FileName);
	bool LoadJsonFromFile(FString& _OutJson, FString _FileName);

	template<typename Struct_Type>
	FString CreateDataToJson(Struct_Type& _Data)
	{
		//JsonWriter로 쓸 준비
		FString jsonData{};
		TSharedRef<TJsonWriter<TCHAR>> jsonWriter = TJsonWriterFactory<>::Create(&jsonData);

		//리플렉션을 활용해 카테고리로 json을 저장하기 때문에
		//카테고리 이름을 중복되지 않게 지정한다
		//구조체의 필드를 돌면서 카테고리 이름으로 json의 오브젝트 필드를 생성하고 데이터를 쓴다
		FString categoryName = TEXT("None");
		jsonWriter->WriteObjectStart();
		for (TFieldIterator<FField> fIter(Struct_Type::StaticStruct()); fIter; ++fIter)
		{
			FField* field = *fIter;

			//카테고리 이름이 변경되면 json의 오브젝트 필드를 새로 생성한다
			FString currentCategoryName = field->GetMetaData(TEXT("category"));
			if (categoryName != currentCategoryName)
			{
				if (categoryName != TEXT("None"))
				{
					jsonWriter->WriteObjectEnd();
				}
				categoryName = currentCategoryName;
				jsonWriter->WriteObjectStart(*categoryName);
			}
			JsonWriteByField(&_Data, field, jsonWriter);
		}
		jsonWriter->WriteObjectEnd();
		jsonWriter->WriteObjectEnd();
		jsonWriter->Close();

		return jsonData;
	}

	template<typename Struct_Type>
	Struct_Type LoadDataFromJson(FString _Json)
	{
		//구조체를 하나 만들고 그 구조체에 json데이터를 쓰기위해
		//json을 읽어들일 준비를 한다
		Struct_Type loadData{};
		TSharedRef<TJsonReader<TCHAR>> jsonReader = TJsonReaderFactory<TCHAR>::Create(MoveTemp(_Json));
		TSharedPtr<FJsonObject> json = MakeShareable(new FJsonObject());

		//리플렉션을 활용해 json의 오브젝트 필드를 읽기 때문에
		//처음에 오브젝트 필드를 중복되지 않는 값으로 지정한다
		FString objectFeildName = TEXT("None");
		check(FJsonSerializer::Deserialize(jsonReader, json) && json.IsValid());
		const TSharedPtr<FJsonObject>* jsonObj{};
		for (TFieldIterator<FField> fIter(Struct_Type::StaticStruct()); fIter; ++fIter)
		{
			FField* field = *fIter;

			//카테고리 이름이 변경되면 변경된 오브젝트 필드를 읽어들인다
			FString currentCategoryName = field->GetMetaData(TEXT("category"));
			if (objectFeildName != currentCategoryName)
			{
				objectFeildName = currentCategoryName;
				check(json->TryGetObjectField(objectFeildName, jsonObj));
			}
			JsonReadByField(&loadData, field, jsonObj->Get());
		}

		return loadData;
	}

private:
	void PrintPlayerData(const FPlayerData& _PlayerData);

	void OnPostRequestComplete(FHttpRequestPtr _Request, FHttpResponsePtr _Response, bool _bWasSuccessful);

	bool JsonWriteByField(void* _Container, FField* _Field, TSharedRef<TJsonWriter<TCHAR>>& _JsonWriter);
	bool JsonReadByField(void* _Container, FField* _Field, FJsonObject* _JsonObj);

	template<typename Struct_Type>
	bool WriteStructArrayJson(void* _Container, FArrayProperty* _ArrayProperty, TSharedRef<TJsonWriter<TCHAR>>& _JsonWriter)
	{
		//배열 또한 리플렉션을 통해 동적으로 쓰기 위해
		//배열 쓰기를 따로 처리를 해준다
		FScriptArray* sArr = _ArrayProperty->GetPropertyValuePtr_InContainer(_Container);
		TArray<Struct_Type> structArray = (TArray<Struct_Type>&)(*sArr);
		_JsonWriter->WriteArrayStart(*Struct_Type::StaticStruct()->GetName());
		for (auto& structure : structArray)
		{
			_JsonWriter->WriteObjectStart();
			for (TFieldIterator<FProperty> fIter(Struct_Type::StaticStruct()); fIter; ++fIter)
			{
				FField* field = *fIter;
				if (!JsonWriteByField(&structure, field, _JsonWriter))
				{
					return false;
				}
			}
			_JsonWriter->WriteObjectEnd();
		}
		_JsonWriter->WriteArrayEnd();
		return true;
	}

	template<typename Struct_Type>
	bool ReadStructArrayJson(void* _Container, FArrayProperty* _ArrayProperty, const TArray<TSharedPtr<FJsonValue>>* _JsonArray)
	{
		//배열 또한 리플렉션을 통해 동적으로 읽어들이기 위해
		//배열 읽기를 따로 처리를 해준다
		TArray<Struct_Type> structArray{};
		Struct_Type structure{};

		for (auto& arrayField : *_JsonArray)
		{
			auto& obj = arrayField->AsObject();
			for (TFieldIterator<FProperty> fIter(Struct_Type::StaticStruct()); fIter; ++fIter)
			{
				FField* field = *fIter;
				if (!JsonReadByField(&structure, field, obj.Get()))
				{
					return false;
				}
			}
			structArray.Emplace(structure);
		}
		FScriptArray* sArr = (FScriptArray*)&structArray;
		_ArrayProperty->SetValue_InContainer(_Container, *sArr);

		return true;
	}
};
