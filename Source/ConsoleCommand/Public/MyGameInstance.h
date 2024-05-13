// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

extern TAutoConsoleVariable<float> CVarCommand;

/**
 * 
 */
UCLASS()
class CONSOLECOMMAND_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:

protected:

private:

public:
	UMyGameInstance();
	void Init()override;

	UFUNCTION(Exec)
	void ConsoleCmdTest_Exec(const FString& _Str);

protected:

private:
	UFUNCTION()
	void ConsoleCmdTest_Regist(const TArray<FString>& _Args);
};
