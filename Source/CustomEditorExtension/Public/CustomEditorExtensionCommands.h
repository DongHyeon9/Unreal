// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "CustomEditorExtensionStyle.h"

class FCustomEditorExtensionCommands : public TCommands<FCustomEditorExtensionCommands>
{
public:

	FCustomEditorExtensionCommands()
		: TCommands<FCustomEditorExtensionCommands>(TEXT("CustomEditorExtension"), NSLOCTEXT("Contexts", "CustomEditorExtension", "CustomEditorExtension Plugin"), NAME_None, FCustomEditorExtensionStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
