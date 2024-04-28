// Fill out your copyright notice in the Description page of Project Settings.


#include "JSGameInstance.h"

#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Kismet/KismetSystemLibrary.h"

UJSGameInstance::UJSGameInstance()
{
}

void UJSGameInstance::Init()
{
	Super::Init();

	FPlayerData playerData{};
	FString jsonData{};

	jsonData = CreateDataToJson<FPlayerData>(playerData);
	SaveJsonToFile(jsonData, TEXT("JsonTest"));

	LoadJsonFromFile(jsonData, TEXT("JsonTest"));
	playerData = LoadDataFromJson<FPlayerData>(jsonData);

	PrintPlayerData(playerData);
}

void UJSGameInstance::PostJson(FString _Json, FString _IP)
{
	TSharedRef<IHttpRequest> httpRequest = FHttpModule::Get().CreateRequest();
	httpRequest->SetVerb("POST");
	httpRequest->SetURL(_IP);
	httpRequest->SetHeader("Content-Type", "application/json");
	httpRequest->OnProcessRequestComplete().BindUObject(this, &UJSGameInstance::OnPostRequestComplete);
	httpRequest->SetContentAsString(MoveTemp(_Json));
	httpRequest->ProcessRequest();
}

bool UJSGameInstance::SaveJsonToFile(FString _Json, FString _FileName)
{
	FString directory = UKismetSystemLibrary::GetProjectSavedDirectory() + _FileName;
	return FFileHelper::SaveStringToFile(*MoveTemp(_Json), *directory);
}

bool UJSGameInstance::LoadJsonFromFile(FString& _OutJson, FString _FileName)
{
	FString directory = UKismetSystemLibrary::GetProjectSavedDirectory() + _FileName;
	return FFileHelper::LoadFileToString(_OutJson, *directory);
}

void UJSGameInstance::PrintPlayerData(const FPlayerData& _PlayerData)
{
	UE_LOG(LogTemp, Log, TEXT("===================="));

	UE_LOG(LogTemp, Warning, TEXT("userName : %s"), *_PlayerData.userName);
	UE_LOG(LogTemp, Warning, TEXT("characterClass : %d"), (uint8)_PlayerData.characterClass);
	UE_LOG(LogTemp, Warning, TEXT("level : %d"), _PlayerData.level);
	UE_LOG(LogTemp, Warning, TEXT("damage : %d"), _PlayerData.damage);
	UE_LOG(LogTemp, Warning, TEXT("armor : %d"), _PlayerData.armor);
	for (auto& skill : _PlayerData.skilldata)
	{
		UE_LOG(LogTemp, Warning, TEXT("skillName : %s"), *skill.skillName);
		UE_LOG(LogTemp, Warning, TEXT("skillLevel : %d"), skill.skillLevel);
	}

	UE_LOG(LogTemp, Log, TEXT("===================="));
}

void UJSGameInstance::OnPostRequestComplete(FHttpRequestPtr _Request, FHttpResponsePtr _Response, bool _bWasSuccessful)
{
	if (_bWasSuccessful && _Response.IsValid())
	{
		FString request = _Response->GetContentAsString();

		//request 메시지로 작업
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Post request fail"));
	}
}

bool UJSGameInstance::JsonWriteByField(void* _Container, FField* _Field, TSharedRef<TJsonWriter<TCHAR>>& _JsonWriter)
{
	//각 필드에 맞는 값으로 PropertyField를 캐스팅해줘서
	//각 필드에 맞는 형식으로 json을 쓴다
	if (auto floatProperty = CastField<FFloatProperty>(_Field))
	{
		float value{};
		floatProperty->GetValue_InContainer(_Container, &value);
		_JsonWriter->WriteValue(*_Field->GetName(), value);
	}

	else if (auto enumProperty = CastField<FEnumProperty>(_Field))
	{
		uint8 value{};
		enumProperty->GetValue_InContainer(_Container, &value);
		_JsonWriter->WriteValue(*_Field->GetName(), value);
	}

	else if (auto strProperty = CastField<FStrProperty>(_Field))
	{
		FString value{};
		strProperty->GetValue_InContainer(_Container, &value);
		_JsonWriter->WriteValue(*_Field->GetName(), value);
	}

	else if (auto intProperty = CastField<FIntProperty>(_Field))
	{
		int32 value{};
		intProperty->GetValue_InContainer(_Container, &value);
		_JsonWriter->WriteValue(*_Field->GetName(), value);
	}

	else if (auto arrayProperty = CastField<FArrayProperty>(_Field))
	{
		if (auto structProperty = CastField<FStructProperty>(arrayProperty->Inner))
		{
			if (FSkillData::StaticStruct()->GetName() == structProperty->Struct->GetName())
			{
				checkf(WriteStructArrayJson<FSkillData>(_Container, arrayProperty, _JsonWriter), TEXT("Struct Write Fail"));
			}
			else
			{
				//else if에 추가하고싶은 Struct타입
				checkf(false, TEXT("Unkwon Struct Type"));
			}
		}
		else
		{
			//else if에 TArray 타입
			checkf(false, TEXT("Unkwon Array Type"));
		}
	}
	else
	{
		//else if에 추가하고싶은 FProperty타입
		checkf(false, TEXT("Unkwon FProperty Type"));
	}
	return true;
}

bool UJSGameInstance::JsonReadByField(void* _Container, FField* _Field, FJsonObject* _JsonObj)
{
	//각 필드에 맞는 값으로 PropertyField를 캐스팅해줘서
	//각 필드에 맞는 형식으로 json을 읽는다
	if (auto floatProperty = CastField<FFloatProperty>(_Field))
	{
		float value{};
		check(_JsonObj->TryGetNumberField(*_Field->GetName(), value));
		floatProperty->SetValue_InContainer(_Container, value);
	}

	else if (auto enumProperty = CastField<FEnumProperty>(_Field))
	{
		uint8 value{};
		check(_JsonObj->TryGetNumberField(*_Field->GetName(), value));
		enumProperty->SetValue_InContainer(_Container, &value);
	}

	else if (auto strProperty = CastField<FStrProperty>(_Field))
	{
		FString value{};
		check(_JsonObj->TryGetStringField(*_Field->GetName(), value));
		strProperty->SetValue_InContainer(_Container, value);
	}

	else if (auto intProperty = CastField<FIntProperty>(_Field))
	{
		int32 value{};
		check(_JsonObj->TryGetNumberField(*_Field->GetName(), value));
		intProperty->SetValue_InContainer(_Container, value);
	}

	else if (auto arrayProperty = CastField<FArrayProperty>(_Field))
	{
		if (auto structProperty = CastField<FStructProperty>(arrayProperty->Inner))
		{
			const TArray<TSharedPtr<FJsonValue>>* jsonArray{};
			check(_JsonObj->TryGetArrayField(*_Field->GetName(), jsonArray));
			if (FSkillData::StaticStruct()->GetName() == structProperty->Struct->GetName())
			{
				checkf(ReadStructArrayJson<FSkillData>(_Container, arrayProperty, jsonArray), TEXT("Struct Write Fail"));
			}
			else
			{
				//else if에 추가하고싶은 Struct타입
				checkf(false, TEXT("Unkwon Struct Type"));
			}
		}
		else
		{
			//else if에 TArray 타입
			checkf(false, TEXT("Unkwon Array Type"));
		}
	}
	else
	{
		//else if에 추가하고싶은 FProperty타입
		checkf(false, TEXT("Unkwon FProperty Type"));
	}

	return true;
}
