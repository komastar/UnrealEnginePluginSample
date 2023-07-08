// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "WildMiniEditorStyle.h"

class FWildMiniEditorCommands : public TCommands<FWildMiniEditorCommands>
{
public:

	FWildMiniEditorCommands()
		: TCommands<FWildMiniEditorCommands>(TEXT("WildMiniEditor"), NSLOCTEXT("Contexts", "WildMiniEditor", "WildMiniEditor Plugin"), NAME_None, FWildMiniEditorStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};