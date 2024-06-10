// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAsset/NNAssetAction.h"
#include "CustomAsset/NNAsset.h"
#include "CustomAsset/NNAssetEditorApp.h"

FNNAssetAction::FNNAssetAction(EAssetTypeCategories::Type _Category):
	assetCategory(_Category)
{
}

FText FNNAssetAction::GetName() const
{
	return FText::FromString(TEXT("NiceNews 에셋"));
}

FColor FNNAssetAction::GetTypeColor() const
{
	return FColor::FromHex(TEXT("00FFFFFF"));
}

UClass* FNNAssetAction::GetSupportedClass() const
{
	return UNNAsset::StaticClass();
}

void FNNAssetAction::OpenAssetEditor(const TArray<UObject*>& _InObjects, TSharedPtr<class IToolkitHost> _EditWithinLevelEditor)
{
	EToolkitMode::Type mode = _EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;
	for (auto obj : _InObjects) {
		TObjectPtr<UNNAsset> asset = Cast<UNNAsset>(obj);
		if (asset != nullptr) {
			TSharedRef<FNNAssetEditorApp> editor(new FNNAssetEditorApp());
			editor->InitEditor(mode, _EditWithinLevelEditor, asset);
		}
	}
}

uint32 FNNAssetAction::GetCategories()
{
	return assetCategory;
}

const TArray<FText>& FNNAssetAction::GetSubMenus() const
{
	static const TArray<FText> subMenus
	{
		INVTEXT("대대분류"),
		INVTEXT("대중분류"),
		INVTEXT("대소분류"),
		INVTEXT("중대분류"),
		INVTEXT("중중분류"),
		INVTEXT("중소분류"),
		INVTEXT("소대분류"),
		INVTEXT("소중분류"),
		INVTEXT("소소분류"),
	};
	return subMenus;
}
