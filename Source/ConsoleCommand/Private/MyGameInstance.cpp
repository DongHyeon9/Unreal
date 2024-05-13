// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "HAL/IConsoleManager.h"

UMyGameInstance::UMyGameInstance()
{
}

void UMyGameInstance::Init()
{
	Super::Init();

	FConsoleCommandWithArgsDelegate cmdDelegate{};

	cmdDelegate.BindUObject(this, &UMyGameInstance::ConsoleCmdTest_Regist);

	IConsoleManager::Get().RegisterConsoleCommand(
		TEXT("ConsoleCmdTest_Regist"),
		TEXT("주석 달리는 곳"), cmdDelegate);
}

void UMyGameInstance::ConsoleCmdTest_Exec(const FString& _Str)
{
	UE_LOG(LogTemp, Warning, TEXT("Exec : %s, %.2f"), *_Str, CVarCommand.GetValueOnGameThread());
}

void UMyGameInstance::ConsoleCmdTest_Regist(const TArray<FString>& _Args)
{
	FString string{};
	for (const auto& str : _Args)
		string += str;
	UE_LOG(LogTemp, Warning, TEXT("Regist : %s, %.2f"), *string, CVarCommand.GetValueOnGameThread());
}

TAutoConsoleVariable<float> CVarCommand(TEXT("r.customVar"), 0.f, TEXT("주석 달리는 곳"), ECVF_Default);