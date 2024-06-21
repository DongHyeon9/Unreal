// Copyright Epic Games, Inc. All Rights Reserved.

#include "CustomEditorExtension.h"
#include "CustomEditorExtensionStyle.h"
#include "CustomEditorExtensionCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"
#include "EditorUtilityWidget.h"
#include "EditorUtilitySubsystem.h"
#include "EditorUtilityWidgetBlueprint.h"

static const FName CustomEditorExtensionTabName("CustomEditorExtension");

#define LOCTEXT_NAMESPACE "FCustomEditorExtensionModule"

void FCustomEditorExtensionModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FCustomEditorExtensionStyle::Initialize();
	FCustomEditorExtensionStyle::ReloadTextures();

	FCustomEditorExtensionCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FCustomEditorExtensionCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FCustomEditorExtensionModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FCustomEditorExtensionModule::RegisterMenus));
}

void FCustomEditorExtensionModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FCustomEditorExtensionStyle::Shutdown();

	FCustomEditorExtensionCommands::Unregister();
}

void FCustomEditorExtensionModule::PluginButtonClicked()
{
	TObjectPtr<UEditorUtilitySubsystem> editorUtilitySubsystem = GEditor->GetEditorSubsystem<UEditorUtilitySubsystem>();

	TObjectPtr<UEditorUtilityWidgetBlueprint> blueprintWidget = LoadObject<UEditorUtilityWidgetBlueprint>(nullptr, L"/CustomEditorExtension/BlueprintEditorWidget");
	TObjectPtr<UEditorUtilityWidgetBlueprint> cppWidget = LoadObject<UEditorUtilityWidgetBlueprint>(nullptr, L"/CustomEditorExtension/CppEditorWidget");

	editorUtilitySubsystem->SpawnAndRegisterTab(blueprintWidget);
	editorUtilitySubsystem->SpawnAndRegisterTab(cppWidget);
}

void FCustomEditorExtensionModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FCustomEditorExtensionCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FCustomEditorExtensionCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCustomEditorExtensionModule, CustomEditorExtension)