// Copyright Epic Games, Inc. All Rights Reserved.

#include "CustomAssetEditor.h"
#include "CustomAsset/NNAssetAction.h"
#include "DerivedAsset/NNMatInstConstAction.h"

#include "IAssetTools.h"
#include "AssetToolsModule.h"

#define LOCTEXT_NAMESPACE "FCustomAssetEditorModule"

void FCustomAssetEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	// 에셋 에디터에 원하는 에셋들을 원하는 카테고리에 등록
	IAssetTools& assetToolsModule = IAssetTools::Get();

	EAssetTypeCategories::Type assetType = assetToolsModule.RegisterAdvancedAssetCategory(FName(TEXT("NNCustomAssetEditor")), FText::FromString(TEXT("NiceNews에셋")));

	TSharedPtr<FNNMatInstConstAction> derivedAssetAction = MakeShareable(new FNNMatInstConstAction{ assetType });
	TSharedPtr<FNNAssetAction> CustomAssetAction = MakeShareable(new FNNAssetAction{ assetType });

	assetToolsModule.RegisterAssetTypeActions(derivedAssetAction.ToSharedRef());
	assetToolsModule.RegisterAssetTypeActions(CustomAssetAction.ToSharedRef());
}

void FCustomAssetEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCustomAssetEditorModule, CustomAssetEditor)