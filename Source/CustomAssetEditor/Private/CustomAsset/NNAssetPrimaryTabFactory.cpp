// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAsset/NNAssetPrimaryTabFactory.h"
#include "CustomAsset/NNAssetEditorApp.h"
#include "CustomAsset/NNAsset.h"

#include "IDetailsView.h"
#include "PropertyEditorModule.h"

FNNAssetPrimaryTabFactory::FNNAssetPrimaryTabFactory(TSharedPtr<FNNAssetEditorApp> _App):
	FWorkflowTabFactory(FName(TEXT("FNNAssetPrimaryTab")), _App)
{
	app = _App;
	TabLabel = FText::FromString(TEXT("Tab Label"));
	ViewMenuDescription = FText::FromString(TEXT("View Menu Description"));
	ViewMenuTooltip = FText::FromString(TEXT("View Menu Tooltip"));
}

TSharedRef<SWidget> FNNAssetPrimaryTabFactory::CreateTabBody(const FWorkflowTabSpawnInfo& _Info) const
{
	TSharedPtr<FNNAssetEditorApp> editorApp = app.Pin();
	FPropertyEditorModule& propertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>(TEXT("PropertyEditor"));

	FDetailsViewArgs detailsViewArgs{};
	detailsViewArgs.bAllowSearch = false;
	detailsViewArgs.bHideSelectionTip = true;
	detailsViewArgs.bLockable = false;
	detailsViewArgs.bSearchInitialKeyFocus = true;
	detailsViewArgs.bUpdatesFromSelection = false;
	detailsViewArgs.NotifyHook = nullptr;
	detailsViewArgs.bShowOptions = true;
	detailsViewArgs.bShowModifiedPropertiesOption = true;
	detailsViewArgs.bShowScrollBar = false;

	TSharedPtr<IDetailsView> detailsView = propertyEditorModule.CreateDetailView(detailsViewArgs);
	detailsView->SetObject(editorApp->GetWorkingAsset());

	return SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.FillHeight(1.f)
		.HAlign(HAlign_Fill)
		[
			detailsView.ToSharedRef()
		];
}

FText FNNAssetPrimaryTabFactory::GetTabToolTipText(const FWorkflowTabSpawnInfo& _Info) const
{
	return FText::FromString(TEXT("Tab ToolTip Text"));
}
