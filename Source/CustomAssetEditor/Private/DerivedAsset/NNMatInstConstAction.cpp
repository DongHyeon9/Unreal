// Fill out your copyright notice in the Description page of Project Settings.


#include "DerivedAsset/NNMatInstConstAction.h"
#include "DerivedAsset/NNMatInstConst.h"

#include "MaterialEditor/Public/MaterialEditorModule.h"

FNNMatInstConstAction::FNNMatInstConstAction(EAssetTypeCategories::Type _Category):
	assetCategory(_Category)
{
}

FText FNNMatInstConstAction::GetName() const
{
	return FText::FromString(TEXT("NiceNews 재질"));
}

FColor FNNMatInstConstAction::GetTypeColor() const
{
	return FColor::FromHex(TEXT("00FF00FF"));
}

UClass* FNNMatInstConstAction::GetSupportedClass() const
{
	return UNNMatInstConst::StaticClass();
}

void FNNMatInstConstAction::OpenAssetEditor(const TArray<UObject*>& _InObjects, TSharedPtr<class IToolkitHost> _EditWithinLevelEditor)
{
	EToolkitMode::Type mode = _EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for (auto obj : _InObjects)
	{
		auto matInstConst = Cast<UMaterialInstanceConstant>(obj);
		if (matInstConst != NULL)
		{
			IMaterialEditorModule* materialEditorModule = &FModuleManager::LoadModuleChecked<IMaterialEditorModule>("MaterialEditor");
			materialEditorModule->CreateMaterialInstanceEditor(mode, _EditWithinLevelEditor, matInstConst);
		}
	}
}

uint32 FNNMatInstConstAction::GetCategories()
{
	return assetCategory;
}

const TArray<FText>& FNNMatInstConstAction::GetSubMenus() const
{
	static const TArray<FText> subMenus
	{
		INVTEXT("머티리얼"),
	};
	return subMenus;
}
