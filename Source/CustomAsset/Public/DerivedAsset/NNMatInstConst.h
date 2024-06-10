// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Materials/MaterialInstanceConstant.h"
#include "NNMatInstConst.generated.h"

/**
 * UMaterialInstanceConstant::StaticClass() 키의 중복을 피하기 위한 파생클래스
 */
UCLASS()
class CUSTOMASSET_API UNNMatInstConst : public UMaterialInstanceConstant
{
	GENERATED_BODY()
	
};
