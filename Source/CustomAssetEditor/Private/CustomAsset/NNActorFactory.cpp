// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAsset/NNActorFactory.h"
#include "CustomAsset/NNAsset.h"
#include "CustomAsset/NNActor.h"

UNNActorFactory::UNNActorFactory(const FObjectInitializer& _ObjectInitializer)
{
	DisplayName = FText::FromString("NiceNews 에셋");
	NewActorClass = ANNActor::StaticClass();
}

void UNNActorFactory::PostSpawnActor(UObject* _Asset, AActor* _NewActor)
{
	Super::PostSpawnActor(_Asset, _NewActor);

	auto asset = CastChecked<UNNAsset>(_Asset);
	auto actor = CastChecked<ANNActor>(_NewActor);
	//에셋에 들어있던 값 셋팅
	FProperty* assetColor = UNNAsset::StaticClass()->FindPropertyByName(TEXT("defaultColor"));
	FProperty* actorColor = ANNActor::StaticClass()->FindPropertyByName(TEXT("meshColor"));

	FColor outColor{};

	assetColor->GetValue_InContainer(asset, &outColor);
	actorColor->SetValue_InContainer(actor, &outColor);
}

void UNNActorFactory::PostCreateBlueprint(UObject* _Asset, AActor* _CDO)
{
	if (_Asset != nullptr && _CDO != nullptr) {
		auto asset = CastChecked<UNNAsset>(_Asset);
		auto actor = CastChecked<ANNActor>(_CDO);

		//에셋에 들어있던 값 셋팅
		FProperty* assetColor = UNNAsset::StaticClass()->FindPropertyByName(TEXT("defaultColor"));
		FProperty* actorColor = ANNActor::StaticClass()->FindPropertyByName(TEXT("meshColor"));

		FColor outColor{};

		assetColor->GetValue_InContainer(asset, &outColor);
		actorColor->SetValue_InContainer(actor, &outColor);
	}
}

bool UNNActorFactory::CanCreateActorFrom(const FAssetData& _AssetData, FText& _OutErrorMsg)
{
	if (!_AssetData.IsValid() || !_AssetData.IsInstanceOf(UNNAsset::StaticClass()))
	{
		_OutErrorMsg = NSLOCTEXT("CanCreateActor", "NoSystem", "에셋 데이터가 없음");
		return false;
	}

	return true;
}