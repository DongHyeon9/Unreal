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

	bool SaveJsonToFile(const FString& _Json, FString _FileName);
	bool LoadJsonFromFile(FString& _OutJson, FString _FileName);

	template<typename Struct_Type>
	FString CreateDataToJson(Struct_Type& _Data)
	{
		//JsonWriter�� �� �غ�
		FString jsonData{};
		TSharedRef<TJsonWriter<TCHAR>> jsonWriter = TJsonWriterFactory<>::Create(&jsonData);

		//���÷����� Ȱ���� ī�װ��� json�� �����ϱ� ������
		//ī�װ� �̸��� �ߺ����� �ʰ� �����Ѵ�
		//����ü�� �ʵ带 ���鼭 ī�װ� �̸����� json�� ������Ʈ �ʵ带 �����ϰ� �����͸� ����
		FString categoryName = TEXT("None");
		jsonWriter->WriteObjectStart();
		for (TFieldIterator<FField> fIter(Struct_Type::StaticStruct()); fIter; ++fIter)
		{
			FField* field = *fIter;

			//ī�װ� �̸��� ����Ǹ� json�� ������Ʈ �ʵ带 ���� �����Ѵ�
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
		//����ü�� �ϳ� ����� �� ����ü�� json�����͸� ��������
		//json�� �о���� �غ� �Ѵ�
		Struct_Type loadData{};
		TSharedRef<TJsonReader<TCHAR>> jsonReader = TJsonReaderFactory<TCHAR>::Create(_Json);
		TSharedPtr<FJsonObject> json = MakeShareable(new FJsonObject());

		//���÷����� Ȱ���� json�� ������Ʈ �ʵ带 �б� ������
		//ó���� ������Ʈ �ʵ带 �ߺ����� �ʴ� ������ �����Ѵ�
		FString objectFeildName = TEXT("None");
		check(FJsonSerializer::Deserialize(jsonReader, json) && json.IsValid());
		const TSharedPtr<FJsonObject>* jsonObj{};
		for (TFieldIterator<FField> fIter(Struct_Type::StaticStruct()); fIter; ++fIter)
		{
			FField* field = *fIter;

			//ī�װ� �̸��� ����Ǹ� ����� ������Ʈ �ʵ带 �о���δ�
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
		//�迭 ���� ���÷����� ���� �������� ���� ����
		//�迭 ���⸦ ���� ó���� ���ش�
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
		//�迭 ���� ���÷����� ���� �������� �о���̱� ����
		//�迭 �б⸦ ���� ó���� ���ش�
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