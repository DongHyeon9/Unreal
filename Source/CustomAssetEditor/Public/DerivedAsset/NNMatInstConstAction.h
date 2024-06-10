// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

class IToolKiyHost;
/**
 * 에셋 에디터에서 머티리얼 인스턴스를 등록시켜줌
 */
class CUSTOMASSETEDITOR_API FNNMatInstConstAction : public FAssetTypeActions_Base
{
public:

protected:

private:
	EAssetTypeCategories::Type assetCategory;

public:
	FNNMatInstConstAction(EAssetTypeCategories::Type _Category);
	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual void OpenAssetEditor(const TArray<UObject*>& _InObjects, TSharedPtr<class IToolkitHost> _EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;
	virtual uint32 GetCategories() override;
	virtual const TArray<FText>& GetSubMenus() const override;

protected:

private:

};
