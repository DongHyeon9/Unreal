// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/MaterialInstanceConstantFactoryNew.h"
#include "NNMatInstConstFactory.generated.h"

/**
 * FNNMatInstConstAction���� ����� ��Ƽ������ ������·� ������ų�� �����ϴ� Factory
 */
UCLASS()
class CUSTOMASSETEDITOR_API UNNMatInstConstFactory : public UMaterialInstanceConstantFactoryNew
{
	GENERATED_BODY()
public:
	UNNMatInstConstFactory(const FObjectInitializer& _ObjectInitializer);

	virtual bool CanCreateNew()const override { return true; }
};
