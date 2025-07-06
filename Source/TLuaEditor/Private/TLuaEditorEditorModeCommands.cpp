// Copyright Epic Games, Inc. All Rights Reserved.

#include "TLuaEditorEditorModeCommands.h"
#include "TLuaEditorEditorMode.h"
#include "EditorStyleSet.h"

#define LOCTEXT_NAMESPACE "TLuaEditorEditorModeCommands"

FTLuaEditorEditorModeCommands::FTLuaEditorEditorModeCommands()
	: TCommands<FTLuaEditorEditorModeCommands>("TLuaEditorEditorMode",
		NSLOCTEXT("TLuaEditorEditorMode", "TLuaEditorEditorModeCommands", "TLuaEditor Editor Mode"),
		NAME_None,
		FEditorStyle::GetStyleSetName())
{
}

void FTLuaEditorEditorModeCommands::RegisterCommands()
{
	TArray <TSharedPtr<FUICommandInfo>>& ToolCommands = Commands.FindOrAdd(NAME_Default);

	UI_COMMAND(SimpleTool, "Show Actor Info", "Opens message box with info about a clicked actor", EUserInterfaceActionType::Button, FInputChord());
	ToolCommands.Add(SimpleTool);

	UI_COMMAND(InteractiveTool, "Measure Distance", "Measures distance between 2 points (click to set origin, shift-click to set end point)", EUserInterfaceActionType::ToggleButton, FInputChord());
	ToolCommands.Add(InteractiveTool);
}

TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> FTLuaEditorEditorModeCommands::GetCommands()
{
	return FTLuaEditorEditorModeCommands::Get().Commands;
}

#undef LOCTEXT_NAMESPACE
