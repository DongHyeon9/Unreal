// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAsset/NNActor.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"

ANNActor::ANNActor()
{
	PrimaryActorTick.bCanEverTick = true;

	rootComp = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	RootComponent = rootComp;
	mesh->SetupAttachment(rootComp);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_SPHERE(TEXT("/CustomAssetEditor/SM_Sphere"));

	if (SM_SPHERE.Succeeded()) {
		mesh->SetStaticMesh(SM_SPHERE.Object);
		dynamicMaterial = UMaterialInstanceDynamic::Create(SM_SPHERE.Object->GetMaterial(0), GetWorld());
		mesh->SetMaterial(0, dynamicMaterial);
	}
}

void ANNActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (dynamicMaterial != nullptr)
		dynamicMaterial->SetVectorParameterValue(FName("Color"), meshColor);
}

