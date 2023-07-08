// Copyright Epic Games, Inc. All Rights Reserved.

#include "WildMiniEditor.h"
#include "WildMiniEditorStyle.h"
#include "WildMiniEditorCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName EditorWindowPluginTabName("WildMiniEditor");

#define LOCTEXT_NAMESPACE "FWildMiniEditorModule"

void FWildMiniEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FWildMiniEditorStyle::Initialize();
	FWildMiniEditorStyle::ReloadTextures();

	FWildMiniEditorCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FWildMiniEditorCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FWildMiniEditorModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FWildMiniEditorModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(EditorWindowPluginTabName, FOnSpawnTab::CreateRaw(this, &FWildMiniEditorModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FEditorWindowPluginTabTitle", "FWildMiniEditorModule"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FWildMiniEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FWildMiniEditorStyle::Shutdown();

	FWildMiniEditorCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(EditorWindowPluginTabName);
}

TSharedRef<SDockTab> FWildMiniEditorModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FWildMiniEditorModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("WildMiniEditor.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FWildMiniEditorModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(EditorWindowPluginTabName);
}

void FWildMiniEditorModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FWildMiniEditorCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FWildMiniEditorCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FWildMiniEditorModule, WildMiniEditor)