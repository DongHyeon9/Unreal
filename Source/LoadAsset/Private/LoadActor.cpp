// Fill out your copyright notice in the Description page of Project Settings.

#include "LoadActor.h"

#include "Components/StaticMeshComponent.h"
#include "Engine/AssetManager.h"

ALoadActor::ALoadActor() :
	data(30)
{
	PrimaryActorTick.bCanEverTick = false;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	cdoLoadComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CdoLoadComp"));
	syncLoadComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SyncLoadComp"));
	asyncLoadComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AsyncLoadComp"));

	RootComponent = rootComp;
	cdoLoadComp->SetupAttachment(rootComp);
	syncLoadComp->SetupAttachment(rootComp);
	asyncLoadComp->SetupAttachment(rootComp);

	cdoLoadComp->SetRelativeLocation(FVector(0.f, 350.f, 0.f));
	asyncLoadComp->SetRelativeLocation(FVector(0.f, -350.f, 0.f));

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_CDO(TEXT("/Game/01_Meshes/SM_CDOLoad"));
	if (SM_CDO.Succeeded())
	{
		cdoLoadComp->SetStaticMesh(SM_CDO.Object);
	}

}

void ALoadActor::BeginPlay()
{
	Super::BeginPlay();
	
	LoadAssetSyncronous();
	LoadAssetAsyncronous();
}

void ALoadActor::OnAssetLoadCompleted()
{
	check(assetStreamingHandle.IsValid());
	TObjectPtr<UStaticMesh> assetLoaded = CastChecked<UStaticMesh>(assetStreamingHandle->GetLoadedAsset());
	check(!assetLoaded.IsNull());

	asyncLoadComp->SetStaticMesh(assetLoaded);
	UE_LOG(LogTemp, Warning, TEXT("%s : Async load success"), *asyncLoadAsset.GetAssetName());
	assetStreamingHandle.Reset();
}

void ALoadActor::LoadAssetAsyncronous()
{
	if (asyncLoadAsset.IsValid())
	{
		TObjectPtr<UStaticMesh> syncloadedAseet = *asyncLoadAsset;
		UE_LOG(LogTemp, Warning, TEXT("%s : Already Loaded"), *syncLoadAsset.GetAssetName());
		asyncLoadComp->SetStaticMesh(syncloadedAseet);
	}
	else
	{
		assetStreamingHandle =
			UAssetManager::GetStreamableManager().RequestAsyncLoad(
				asyncLoadAsset.ToSoftObjectPath(),
				FStreamableDelegate::CreateUObject(this,
					&ALoadActor::OnAssetLoadCompleted));
	}
}

void ALoadActor::LoadAssetSyncronous()
{
	check(!syncLoadAsset.IsNull());
	TObjectPtr<UStaticMesh> syncloadedAseet{};

	if (syncLoadAsset.IsValid())
	{
		syncloadedAseet = *syncLoadAsset;
		UE_LOG(LogTemp, Warning, TEXT("%s : Already Loaded"), *syncLoadAsset.GetAssetName());
	}
	else
	{
		//둘은 비슷한 동작을 하지만
		//밑의 LoadObject는 Path의 경로로 에셋을 로드할 수 있다
		//syncloadedAseet = syncLoadAsset.LoadSynchronous();
		syncloadedAseet = LoadObject<UStaticMesh>(NULL, *syncLoadAsset.GetLongPackageName());
		UE_LOG(LogTemp, Warning, TEXT("%s : Sync load success"), *syncLoadAsset.GetAssetName());
	}

	check(!syncloadedAseet.IsNull());
	syncLoadComp->SetStaticMesh(syncloadedAseet);
}
