// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/WorkflowTabFactory.h"

class FNNAssetEditorApp;
/**
 * Default 창에 탭에 대한 설정
 */
class CUSTOMASSETEDITOR_API FNNAssetPrimaryTabFactory : public FWorkflowTabFactory
{
public:

protected:

private:
	TWeakPtr<FNNAssetEditorApp> app;

public:
	FNNAssetPrimaryTabFactory(TSharedPtr<FNNAssetEditorApp> _App);

	virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& _Info)const override;
	virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& _Info)const override;
protected:

private:

};
