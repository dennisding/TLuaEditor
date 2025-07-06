// Copyright Epic Games, Inc. All Rights Reserved.

#include "TLuaEditorModule.h"
#include "TLuaEditorEditorModeCommands.h"

#define LOCTEXT_NAMESPACE "TLuaEditorModule"

void FTLuaEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module

	FTLuaEditorEditorModeCommands::Register();
}

void FTLuaEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	FTLuaEditorEditorModeCommands::Unregister();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FTLuaEditorModule, TLuaEditorEditorMode)