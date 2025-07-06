// Copyright Epic Games, Inc. All Rights Reserved.

#include "TLuaEditorEditorMode.h"
#include "TLuaEditorEditorModeToolkit.h"
#include "EdModeInteractiveToolsContext.h"
#include "InteractiveToolManager.h"
#include "TLuaEditorEditorModeCommands.h"


//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////// 
// AddYourTool Step 1 - include the header file for your Tools here
//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////// 
#include "Tools/TLuaEditorSimpleTool.h"
#include "Tools/TLuaEditorInteractiveTool.h"

// step 2: register a ToolBuilder in FTLuaEditorEditorMode::Enter() below


#define LOCTEXT_NAMESPACE "TLuaEditorEditorMode"

const FEditorModeID UTLuaEditorEditorMode::EM_TLuaEditorEditorModeId = TEXT("EM_TLuaEditorEditorMode");

FString UTLuaEditorEditorMode::SimpleToolName = TEXT("TLuaEditor_ActorInfoTool");
FString UTLuaEditorEditorMode::InteractiveToolName = TEXT("TLuaEditor_MeasureDistanceTool");


UTLuaEditorEditorMode::UTLuaEditorEditorMode()
{
	FModuleManager::Get().LoadModule("EditorStyle");

	// appearance and icon in the editing mode ribbon can be customized here
	Info = FEditorModeInfo(UTLuaEditorEditorMode::EM_TLuaEditorEditorModeId,
		LOCTEXT("ModeName", "TLuaEditor"),
		FSlateIcon(),
		true);
}


UTLuaEditorEditorMode::~UTLuaEditorEditorMode()
{
}


void UTLuaEditorEditorMode::ActorSelectionChangeNotify()
{
}

void UTLuaEditorEditorMode::Enter()
{
	UEdMode::Enter();

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	// AddYourTool Step 2 - register the ToolBuilders for your Tools here.
	// The string name you pass to the ToolManager is used to select/activate your ToolBuilder later.
	//////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////// 
	const FTLuaEditorEditorModeCommands& SampleToolCommands = FTLuaEditorEditorModeCommands::Get();

	RegisterTool(SampleToolCommands.SimpleTool, SimpleToolName, NewObject<UTLuaEditorSimpleToolBuilder>(this));
	RegisterTool(SampleToolCommands.InteractiveTool, InteractiveToolName, NewObject<UTLuaEditorInteractiveToolBuilder>(this));

	// active tool type is not relevant here, we just set to default
	GetToolManager()->SelectActiveToolType(EToolSide::Left, SimpleToolName);
}

void UTLuaEditorEditorMode::CreateToolkit()
{
	Toolkit = MakeShareable(new FTLuaEditorEditorModeToolkit);
}

TMap<FName, TArray<TSharedPtr<FUICommandInfo>>> UTLuaEditorEditorMode::GetModeCommands() const
{
	return FTLuaEditorEditorModeCommands::Get().GetCommands();
}

#undef LOCTEXT_NAMESPACE
