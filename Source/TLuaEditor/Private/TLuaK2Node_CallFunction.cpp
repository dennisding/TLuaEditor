// Fill out your copyright notice in the Description page of Project Settings.

#include "TLuaK2Node_CallFunction.h"

#include "BlueprintNodeSpawner.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "Kismet2/BlueprintEditorUtils.h"

const FName UTLuaK2Node_CallFunction::DynamicPinPrefix = TEXT("Arg_");

void UTLuaK2Node_CallFunction::AllocateDefaultPins()
{
    bool ConstructBasicPin = Pins.FilterByPredicate(
        [](UEdGraphPin* Pin) {
            return Pin->PinName == FName(TEXT("FunctionName"));
        }).Num() == 0;

    if (ConstructBasicPin) {
       CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);
       CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_String, TEXT("FunctionName"));
       CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Int, TEXT("ArgumentNumber"));

       CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);
       CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Wildcard, TEXT("Result"));
    }

    CreateDynamicPins(GetDynamicPinCount(), TArray<UEdGraphPin*>());
}

UEdGraphPin* UTLuaK2Node_CallFunction::GetArgumentNumberPin() const
{
    return FindPin(TEXT("ArgumentNumber"));
}

int UTLuaK2Node_CallFunction::GetDynamicPinCount() const
{
    auto Pin = GetArgumentNumberPin();
    if (Pin && !Pin->DefaultValue.IsEmpty()) {
        return FCString::Atoi(*Pin->DefaultValue);
    }
    return 0;
}

void UTLuaK2Node_CallFunction::CreateDynamicPins(int Count, const TArray<UEdGraphPin*>& OldPins)
{
    Count = std::min(Count, 15); // limit the Pin Count

    TArray<UEdGraphPin*> PinsToRemove;

    for (UEdGraphPin* Pin : Pins) {
        if (Pin->PinName.ToString().StartsWith(DynamicPinPrefix.ToString())) {
            PinsToRemove.Add(Pin);
        }
    }
    
    for (int i = 0; i < Count; ++i) {
        const FName PinName = *FString::Printf(TEXT("%s%d"), *DynamicPinPrefix.ToString(), i);
        UEdGraphPin* NewPin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Wildcard, PinName);

        for (UEdGraphPin* OldPin : OldPins)
        {
            if (OldPin->PinName == PinName)
            {
                // mark link
                for (UEdGraphPin* LinkedPin : OldPin->LinkedTo) {
                    NewPin->MakeLinkTo(LinkedPin);
                }

                NewPin->DefaultValue = OldPin->DefaultValue;
                NewPin->DefaultObject = OldPin->DefaultObject;
                break;
            }
        }
    }

    // remove pins
    for (UEdGraphPin* Pin : PinsToRemove) {
        RemovePin(Pin);
    }
}

void UTLuaK2Node_CallFunction::ReconstructNode()
{
    Super::ReconstructNode();

    TArray<UEdGraphPin*> OldPins = Pins;

    ReallocatePinsDuringReconstruction(OldPins);
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
    Super::ExpandNode(CompilerContext, SourceGraph);

    UK2Node_CallFunction* CallFunction;
}

void UTLuaK2Node_CallFunction::ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins)
{
    const int32 DynamicPinCount = GetDynamicPinCount();
    CreateDynamicPins(DynamicPinCount, OldPins);
}

void UTLuaK2Node_CallFunction::PinDefaultValueChanged(UEdGraphPin* Pin)
{
    if (Pin && Pin->PinName == TEXT("ArgumentNumber"))
    {
        const int32 NewCount = GetDynamicPinCount();
        const int32 CurrentCount = Pins.FilterByPredicate(
            [](UEdGraphPin* Pin) {
                return Pin->PinName.ToString().StartsWith(DynamicPinPrefix.ToString());
            }).Num();

        if (NewCount != CurrentCount)
        {
            Modify();

            TArray<UEdGraphPin*> OldPins = Pins;
            CreateDynamicPins(GetDynamicPinCount(), OldPins);

            GetGraph()->NotifyGraphChanged();
        }
    }
}

void UTLuaK2Node_CallFunction::PostReconstructNode()
{
    Super::PostReconstructNode();

    const int32 DesiredCount = GetDynamicPinCount();
    const int32 CurrentCount = Pins.FilterByPredicate(
        [](UEdGraphPin* Pin) { return Pin->PinName.ToString().StartsWith(DynamicPinPrefix.ToString()); }
    ).Num();

    if (DesiredCount != CurrentCount)
    {
        Modify();
        GetGraph()->NotifyGraphChanged();
    }
}

void UTLuaK2Node_CallFunction::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
    if (ActionRegistrar.IsOpenForRegistration(GetClass())) {
        UBlueprintNodeSpawner* Spawner = UBlueprintNodeSpawner::Create(GetClass());

        Spawner->DefaultMenuSignature.MenuName = FText::FromString("TLuaCallFunction");

        ActionRegistrar.AddBlueprintAction(GetClass(), Spawner);
    }
}