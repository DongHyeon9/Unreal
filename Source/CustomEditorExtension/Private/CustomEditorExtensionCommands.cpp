// Copyright Epic Games, Inc. All Rights Reserved.

#include "CustomEditorExtensionCommands.h"

#define LOCTEXT_NAMESPACE "FCustomEditorExtensionModule"

void FCustomEditorExtensionCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "CustomEditorExtension", "Execute CustomEditorExtension action", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
