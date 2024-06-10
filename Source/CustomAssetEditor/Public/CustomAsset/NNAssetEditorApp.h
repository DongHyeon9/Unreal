// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/WorkflowCentricApplication.h"

class FTabManager;
class IToolkitHost;
class IToolkit;
class UNNAsset;

/**
 * 
 */
class CUSTOMASSETEDITOR_API FNNAssetEditorApp : public FWorkflowCentricApplication, public FEditorUndoClient, public FNotifyHook
{
public:

protected:

private:
	UNNAsset* workingAsset{};

public:
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& _TabManager)override;
	void InitEditor(const EToolkitMode::Type _Mode, const TSharedPtr<IToolkitHost>& _InitToolkitHost, UObject* _InObject);
	UNNAsset* GetWorkingAsset()const { return workingAsset; }

	//FAssetEditorToolkit interface
	virtual FName GetToolkitFName()const override { return FName{ TEXT("NNAssetEditorApp") }; }
	virtual FText GetBaseToolkitName()const override { return FText::FromString(TEXT("ToolKitName")); }
	virtual FString GetWorldCentricTabPrefix()const override { return TEXT("World Centric Tab Prefix"); }
	virtual FLinearColor GetWorldCentricTabColorScale() const override { return FLinearColor{ 1.f,0.f,1.f }; }
	virtual FString GetDocumentationLink()const override { return TEXT("URL"); }
	virtual void OnToolkitHostingStarted(const TSharedRef<IToolkit>& _Toolkit) override {}
	virtual void OnToolkitHostingFinished(const TSharedRef<IToolkit>& _Toolkit) override {}

protected:

private:

};
