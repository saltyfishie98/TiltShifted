// Fill out your copyright notice in the Description page of Project Settings.

#include "gui/PauseMenu.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/BackgroundBlur.h"
#include "Components/Border.h"
#include "Components/CanvasPanel.h"
#include "Kismet/GameplayStatics.h"
#include "characters/TiltCharacter.h"
#include "gui/SettingsMenu.h"

#pragma region Helpers
void UPauseMenu::checkPlayerController()
{
    if (m_PlayerController == nullptr) {
        UE_LOG(LogTemp, Error, TEXT("PlayerController is NULL"));
        m_PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    }
}
#pragma endregion

void UPauseMenu::PauseGame()
{
    checkPlayerController();
    FInputModeGameAndUI InputMode;

    m_PlayerController->SetPause(true);
    m_PlayerController->SetInputMode(InputMode);
    m_PlayerController->bShowMouseCursor = true;
    AddToViewport();
}

void UPauseMenu::ResumeGame()
{
    checkPlayerController();
    FInputModeGameOnly InputMode;

    UWidgetLayoutLibrary::RemoveAllWidgets(this);
    m_PlayerController->SetInputMode(InputMode);
    m_PlayerController->bShowMouseCursor = false;
    m_PlayerController->SetPause(false);
}

void UPauseMenu::OpenSettings()
{
    SettingsToggled.Broadcast(true);

    if (m_SettingsWidgetInst == nullptr) {
        UE_LOG(LogTemp, Error, TEXT("SettingsWidgetInst is NULL"));
        m_SettingsWidgetInst = CreateWidget<USettingsMenu>(GetWorld(), SettingsWidget);
    }

    if (!m_SettingsWidgetInst)
        return;

    UWidgetLayoutLibrary::RemoveAllWidgets(this);
    m_SettingsWidgetInst->AddToViewport();
}