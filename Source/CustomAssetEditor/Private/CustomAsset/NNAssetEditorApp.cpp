// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAsset/NNAssetEditorApp.h"
#include "CustomAsset/NNAssetAppMode.h"
#include "CustomAsset/NNAsset.h"

void FNNAssetEditorApp::RegisterTabSpawners(const TSharedRef<FTabManager>& _TabManager)
{
	FWorkflowCentricApplication::RegisterTabSpawners(_TabManager);
}

void FNNAssetEditorApp::InitEditor(const EToolkitMode::Type _Mode, const TSharedPtr<IToolkitHost>& _InitToolkitHost, UObject* _InObject)
{
	TArray<UObject*> objectsToEdit{};
	objectsToEdit.Emplace(_InObject);

	workingAsset = Cast<UNNAsset>(_InObject);
	check(workingAsset != nullptr);

	InitAssetEditor(
		_Mode,
		_InitToolkitHost,
		TEXT("NNAssetEditor"),
		FTabManager::FLayout::NullLayout,
		true,	//create standalone menu
		true,	//create defult toolbar
		objectsToEdit);

	AddApplicationMode(TEXT("NNAssetAppMode"), MakeShareable(new FNNAssetAppMode(SharedThis(this))));
	SetCurrentMode(TEXT("NNAssetAppMode"));
}
