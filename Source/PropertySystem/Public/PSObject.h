// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PSObject.generated.h"

/**
 * 
 */
UCLASS()
class PROPERTYSYSTEM_API UPSObject : public UObject
{
	GENERATED_BODY()
public:

protected:

private:
	UPROPERTY()
	FString data;

public:
	UPSObject();

protected:

private:
	UFUNCTION()
	void PrintData(int32 _OtherData);
};
