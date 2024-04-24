// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PSGameInstance.generated.h"

class UPSObject;

/**
 * 
 */
UCLASS()
class PROPERTYSYSTEM_API UPSGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:

protected:

private:
	UPROPERTY()
	TObjectPtr<UPSObject> memberVar;

public:
	UPSGameInstance();

protected:
	virtual void Init()override;

private:

};
