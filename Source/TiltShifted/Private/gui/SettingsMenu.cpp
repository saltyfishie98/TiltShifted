// Fill out your copyright notice in the Description page of Project Settings.

#include "gui/SettingsMenu.h"

void USettingsMenu::Open()
{
    SettingsOpen.Broadcast(true);
    AddToViewport();
}

void USettingsMenu::Close()
{
    SettingsOpen.Broadcast(false);
    RemoveFromParent();
}
