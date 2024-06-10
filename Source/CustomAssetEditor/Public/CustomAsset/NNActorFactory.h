// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "ActorFactories/ActorFactory.h"
#include "NNActorFactory.generated.h"

/**
 * �巡�׾ص������ level�� ���͸� ��ġ�ϱ����� ActorFactory
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
