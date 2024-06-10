// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAsset/NNAssetAppMode.h"
#include "CustomAsset/NNAssetEditorApp.h"
#include "CustomAsset/NNAssetPrimaryTabFactory.h"

FNNAssetAppMode::FNNAssetAppMode(TSharedPtr<FNNAssetEditorApp> _App):
	FApplicationMode(TEXT("NNAssetAppMode"))
{
	app = _App;
	tabs.RegisterFactory(MakeShareable(new FNNAssetPrimaryTabFactory(_App)));

	TabLayout = FTabManager::NewLayout(TEXT("NNAssetAppMode_Layout_v1"))->AddArea(
		FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)->Split(
			FTabManager::NewStack()->AddTab(FName(TEXT("NNAssetPrimaryTab")), ETabState::OpenedTab)));
}

void FNNAssetAppMode::RegisterTabFactories(TSharedPtr<FTabManager> _InManager)
{
	TSharedPtr<FNNAssetEditorApp> editorApp = app.Pin();
	editorApp->PushTabFactories(tabs);
	FApplicationMode::RegisterTabFactories(_InManager);
}

void FNNAssetAppMode::PreDeactivateMode()
{
	FApplicationMode::PreDeactivateMode();
}

void FNNAssetAppMode::PostActivateMode()
{
	FApplicationMode::PostActivateMode();
}
