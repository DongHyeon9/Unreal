// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/ApplicationMode.h"
#include "WorkflowOrientedApp/WorkflowTabManager.h"

class FTabManager;
class FNNAssetEditorApp;

/**
 * 
 */
class CUSTOMASSETEDITOR_API FNNAssetAppMode : public FApplicationMode
{
public:

protected:

private:
	TWeakPtr<FNNAssetEditorApp> app;
	FWorkflowAllowedTabSet tabs;

public:
	FNNAssetAppMode(TSharedPtr<FNNAssetEditorApp> _App);

	virtual void RegisterTabFactories(TSharedPtr<FTabManager> _InManager)override;
	virtual void PreDeactivateMode() override;
	virtual void PostActivateMode() override;

protected:

private:

};
