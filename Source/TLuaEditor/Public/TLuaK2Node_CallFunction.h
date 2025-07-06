// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "K2Node_CallFunction.h"
#include "TLuaK2Node_CallFunction.generated.h"

/**
 * 
 */
UCLASS()
class TLUAEDITOR_API UTLuaK2Node_CallFunction : public UK2Node_CallFunction
{
	GENERATED_BODY()
	
public:
	virtual void ReallocatePinsDuringReconstruction(TArray<UEdGraphPin*>& OldPins) override;
	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FText GetTooltipText() const override;
	virtual void ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;

private:
	int GetArgumentNumber();
};
