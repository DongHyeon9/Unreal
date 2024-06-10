// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

class IToolKiyHost;

/**
 * 
 */
class CUSTOMASSETEDITOR_API FNNAssetAction : public FAssetTypeActions_Base
{
public:

protected:

private:
	EAssetTypeCategories::Type assetCategory;

public:
	FNNAssetAction(EAssetTypeCategories::Type _Category);
	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual void OpenAssetEditor(const TArray<UObject*>& _InObjects, TSharedPtr<class IToolkitHost> _EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;
	virtual uint32 GetCategories() override;
	virtual const TArray<FText>& GetSubMenus() const override;
	
protected:

private:
};
