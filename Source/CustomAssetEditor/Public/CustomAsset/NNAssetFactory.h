// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "NNAssetFactory.generated.h"

/**
 * FNNAssetAction에서 등록한 에셋을 어떠한 형태로 생성시킬지 정의하는 Factory
 */
UCLASS()
class CUSTOMASSETEDITOR_API UNNAssetFactory : public UFactory
{
	GENERATED_BODY()
public:
	UNNAssetFactory(const FObjectInitializer& _ObjectInitializer);

	virtual UObject* FactoryCreateNew(UClass* _InClass, UObject* _InParent, FName _InName, EObjectFlags _Flags, UObject* _Context, FFeedbackContext* _Warn, FName _CallingContext)override;
	virtual bool CanCreateNew()const override { return true; }
};
