// Fill out your copyright notice in the Description page of Project Settings.


#include "DerivedAsset/NNMatInstConstFactory.h"
#include "DerivedAsset/NNMatInstConst.h"

#include "UObject/ConstructorHelpers.h"

UNNMatInstConstFactory::UNNMatInstConstFactory(const FObjectInitializer& _ObjectInitializer)
{
	SupportedClass = UNNMatInstConst::StaticClass();

	static ConstructorHelpers::FObjectFinder<UMaterial> M_MAT(TEXT("/CustomAssetEditor/M_Mat"));
	if (M_MAT.Succeeded())
		InitialParent = M_MAT.Object;
}
