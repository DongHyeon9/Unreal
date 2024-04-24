// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GCObjectNN.generated.h"

/**
 * 
 */
UCLASS()
class GARBAGECOLLECTION_API UGCObjectNN : public UObject
{
	GENERATED_BODY()
public:

protected:

private:
	FString stringData;

public:
	UGCObjectNN();
	void SetStringData(FString _StringData);
	FORCEINLINE const FString& GetStringData()const { return stringData; }

protected:

private:

};
