// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAsset/NNAssetFactory.h"
#include "CustomAsset/NNAsset.h"

UNNAssetFactory::UNNAssetFactory(const FObjectInitializer& _ObjectInitializer):
	Super(_ObjectInitializer)
{
	SupportedClass = UNNAsset::StaticClass();
}

UObject* UNNAssetFactory::FactoryCreateNew(UClass* _InClass, UObject* _InParent, FName _InName, EObjectFlags _Flags, UObject* _Context, FFeedbackContext* _Warn, FName _CallingContext)
{
	TObjectPtr<UNNAsset> asset = NewObject<UNNAsset>(_InParent, _InName, _Flags);
	return asset;
}
