// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "ActorFactories/ActorFactory.h"
#include "NNActorFactory.generated.h"

/**
 * 드래그앤드랍으로 level에 액터를 배치하기위한 ActorFactory
 */
UCLASS(MinimalAPI, config = Editor, collapsecategories, hidecategories = Object)
class UNNActorFactory : public UActorFactory
{
	GENERATED_BODY()
public:
	UNNActorFactory(const FObjectInitializer& _ObjectInitializer);
	virtual void PostSpawnActor(UObject* _Asset, AActor* _NewActor) override;
	virtual void PostCreateBlueprint(UObject* _Asset, AActor* _CDO) override;
	virtual bool CanCreateActorFrom(const FAssetData& _AssetData, FText& _OutErrorMsg) override;

protected:

private:

};
