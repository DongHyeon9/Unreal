// Copyright Epic Games, Inc. All Rights Reserved.

#include "CustomEditorExtensionStyle.h"
#include "CustomEditorExtension.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FCustomEditorExtensionStyle::StyleInstance = nullptr;

void FCustomEditorExtensionStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FCustomEditorExtensionStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FCustomEditorExtensionStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("CustomEditorExtensionStyle"));
	return StyleSetName;
}


const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FCustomEditorExtensionStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("CustomEditorExtensionStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("CustomEditorExtension")->GetBaseDir() / TEXT("Resources"));

	Style->Set("CustomEditorExtension.PluginAction", new IMAGE_BRUSH(TEXT("Icon20"), Icon20x20));
	return Style;
}

void FCustomEditorExtensionStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FCustomEditorExtensionStyle::Get()
{
	return *StyleInstance;
}
