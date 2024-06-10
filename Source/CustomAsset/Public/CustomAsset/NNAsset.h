// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NNAsset.generated.h"

/**
 * 에디터에서 표시될 에셋
 */
UCLASS()
class CUSTOMASSET_API UNNAsset : public UObject
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, category = "NNAsset", meta = (AllowPrivateAccess = true))
	FColor defaultColor;
};
