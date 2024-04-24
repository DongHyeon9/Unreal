// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GCGameInstance.generated.h"

class UGCObjectNN;
class FGCClass;

/**
 * 
 */
UCLASS()
class GARBAGECOLLECTION_API UGCGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:

protected:

private:
	UPROPERTY()
	TObjectPtr<UGCObjectNN> propertyObj;

	UPROPERTY()
	TArray<TObjectPtr<UGCObjectNN>> propertyObjArray;

	TObjectPtr<UGCObjectNN> nonPropertyObj;
	TArray<TObjectPtr<UGCObjectNN>> nonPropertyObjArray;

	UGCObjectNN* derivedFGCObjectScope;
	FGCClass* gcClassMember;

public:
	UGCGameInstance();

protected:
	virtual void Init()override;

private:
	void PrintObjectsState(const TObjectPtr<UGCObjectNN> _Obj);
};
