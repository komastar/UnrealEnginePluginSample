// Copyright Epic Games, Inc. All Rights Reserved.

#include "WildMiniEditorCommands.h"

#define LOCTEXT_NAMESPACE "FWildMiniEditorModule"

void FWildMiniEditorCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "WildMiniEditor", "Bring up WildMiniEditor window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
