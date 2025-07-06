// Copyright Epic Games, Inc. All Rights Reserved.

#include "TLuaEditorEditorModeToolkit.h"
#include "TLuaEditorEditorMode.h"
#include "Engine/Selection.h"

#include "Modules/ModuleManager.h"
#include "PropertyEditorModule.h"
#include "IDetailsView.h"
#include "EditorModeManager.h"

#define LOCTEXT_NAMESPACE "TLuaEditorEditorModeToolkit"

FTLuaEditorEditorModeToolkit::FTLuaEditorEditorModeToolkit()
{
}

void FTLuaEditorEditorModeToolkit::Init(const TSharedPtr<IToolkitHost>& InitToolkitHost, TWeakObjectPtr<UEdMode> InOwningMode)
{
	FModeToolkit::Init(InitToolkitHost, InOwningMode);
}

void FTLuaEditorEditorModeToolkit::GetToolPaletteNames(TArray<FName>& PaletteNames) const
{
	PaletteNames.Add(NAME_Default);
}


FName FTLuaEditorEditorModeToolkit::GetToolkitFName() const
{
	return FName("TLuaEditorEditorMode");
}

FText FTLuaEditorEditorModeToolkit::GetBaseToolkitName() const
{
	return LOCTEXT("DisplayName", "TLuaEditorEditorMode Toolkit");
}

#undef LOCTEXT_NAMESPACE
