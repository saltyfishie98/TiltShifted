// Fill out your copyright notice in the Description page of Project Settings.

#include "gui/SettingsMenu.h"

#pragma region /// Public Methods ///////////////////////////////////////////////////////////////

bool USettingsMenu::Initialize()
{
    Super::Initialize();
    return true;
}

void USettingsMenu::Open()
{
    SettingsOpen.Broadcast(true);
    AddToViewport();
}

void USettingsMenu::Close()
{
    SettingsOpen.Broadcast(false);
    RemoveFromViewport();
}

#pragma endregion
