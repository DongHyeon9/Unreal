// Fill out your copyright notice in the Description page of Project Settings.

#include "PSGameInstance.h"
#include "PSObject.h"

UPSGameInstance::UPSGameInstance()
{
	memberVar = CreateDefaultSubobject<UPSObject>(TEXT("MemberVariable"));
}

void UPSGameInstance::Init()
{
	Super::Init();

	TObjectPtr<UPSObject> CDO = UPSObject::StaticClass()->GetDefaultObject<UPSObject>();
	auto localVariable = NewObject<UPSObject>(this);

	UE_LOG(LogTemp, Log, TEXT("===============변수==============="));
	FProperty* dataProperty = UPSObject::StaticClass()->FindPropertyByName(TEXT("data"));
	if (dataProperty)
	{
		FString outData{};
		FString param = TEXT("지역변수");
		dataProperty->SetValue_InContainer(localVariable, &param);

		param = TEXT("맴버변수");
		dataProperty->SetValue_InContainer(memberVar, &param);

		dataProperty->GetValue_InContainer(CDO, &outData);
		UE_LOG(LogTemp, Warning, TEXT("클래스 디폴트 오브젝트 : %s"), *outData);

		dataProperty->GetValue_InContainer(localVariable, &outData);
		UE_LOG(LogTemp, Warning, TEXT("지역 변수 : %s"), *outData);

		dataProperty->GetValue_InContainer(memberVar, &outData);
		UE_LOG(LogTemp, Warning, TEXT("맴버 변수 : %s"), *outData);
	}
	UE_LOG(LogTemp, Log, TEXT("===============변수==============="));
	UE_LOG(LogTemp, Log, TEXT("===============함수==============="));
	UFunction* printDataFunc = UPSObject::StaticClass()->FindFunctionByName(TEXT("PrintData"));
	if (printDataFunc)
	{
		int32 value{};
		int32* buffer = (int32*)FMemory::Malloc(printDataFunc->ParmsSize);

		value = 30;
		FMemory::Memcpy(buffer, &value, sizeof(int32));
		CDO->ProcessEvent(printDataFunc, buffer);

		value = 20;
		FMemory::Memcpy(buffer, &value, sizeof(int32));
		localVariable->ProcessEvent(printDataFunc, buffer);

		value = 10;
		FMemory::Memcpy(buffer, &value, sizeof(int32));
		memberVar->ProcessEvent(printDataFunc, buffer);

		FMemory::Free(buffer);
	}
	UE_LOG(LogTemp, Log, TEXT("===============함수==============="));
}
