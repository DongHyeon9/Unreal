// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LoadActor.generated.h"

class UStaticMeshComponent;

struct FStreamableHandle;

UCLASS()
class LOADASSET_API ALoadActor : public AActor
{
	GENERATED_BODY()
public:

protected:

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "LoadActorDefaultComp", meta = (AllowPrivateAccess = true))
	TObjectPtr<USceneComponent> rootComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,category="LoadActorDefaultComp",meta=(AllowPrivateAccess =true))
	TObjectPtr<UStaticMeshComponent> cdoLoadComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "LoadActorDefaultComp", meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> syncLoadComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "LoadActorDefaultComp", meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> asyncLoadComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, category = "AssetToLoad", meta = (AllowPrivateAccess = true))
	TSoftObjectPtr<UStaticMesh> syncLoadAsset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, category = "AssetToLoad", meta = (AllowPrivateAccess = true))
	TSoftObjectPtr<UStaticMesh> asyncLoadAsset;
	
	TSharedPtr<FStreamableHandle> assetStreamingHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, category = "Initializer List", meta = (AllowPrivateAccess = true))
	int32 data;

public:
	ALoadActor();

protected:
	virtual void BeginPlay() override;

private:
	void OnAssetLoadCompleted();
	void LoadAssetAsyncronous();
	void LoadAssetSyncronous();
};