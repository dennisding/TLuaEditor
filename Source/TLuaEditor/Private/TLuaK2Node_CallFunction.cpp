// Fill out your copyright notice in the Description page of Project Settings.

#include "TLuaK2Node_CallFunction.h"

#include "BlueprintNodeSpawner.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "Kismet2/BlueprintEditorUtils.h"

void UTLuaK2Node_CallFunction::AllocateDefaultPins()
{
    CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);
    CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_String, TEXT("FunctionName"));
    CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Int, TEXT("ArgumentNumber"));
    //CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Wildcard, TEXT("Arg1"));

    CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);
    //CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_String, TEXT("OutputResult"));
    CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Wildcard, TEXT("Result"));
}

int UTLuaK2Node_CallFunction::GetArgumentNumber()
{
    UEdGraphPin* ArgumentNumberPin = FindPin(TEXT("ArgumentNumber"));
}

FText UTLuaK2Node_CallFunction::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
    return FText::FromString(TEXT("CallLuaFunction"));
}

FText UTLuaK2Node_CallFunction::GetTooltipText() const
{
    return FText::FromString(TEXT("Call lua function"));
//    return TEXT("call lua function");
}

void UTLuaK2Node_CallFunction::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{

}

void UTLuaK2Node_CallFunction::ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins)
{

}

void UTLuaK2Node_CallFunction::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
    if (ActionRegistrar.IsOpenForRegistration(GetClass())) {
        UBlueprintNodeSpawner* Spawner = UBlueprintNodeSpawner::Create(GetClass());

//        Spawner->CustomizeNodeName = FText::FromString("TLua Call Script");
        Spawner->DefaultMenuSignature.MenuName = FText::FromString("TLua|Call Function");

        ActionRegistrar.AddBlueprintAction(GetClass(), Spawner);
    }
}