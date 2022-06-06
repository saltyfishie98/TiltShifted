// Fill out your copyright notice in the Description page of Project Settings.

#include "gui/PauseMenu.h"

#include "Components/BackgroundBlur.h"
#include "Components/Border.h"
#include "Components/CanvasPanel.h"
#include "Kismet/GameplayStatics.h"
#include "characters/TiltCharacter.h"
#include "gui/SettingsMenu.h"

#pragma region /// Helpers //////////////////////////////////////////////////////////////////////

USettingsMenu* UPauseMenu::GetSettingsWidget()
{
    return m_SettingsWidgetInst;
}

#pragma endregion
#pragma region /// Init /////////////////////////////////////////////////////////////////////////

bool UPauseMenu::Initialize()
{
    Super::Initialize();

    m_SettingsWidgetInst = CreateWidget<USettingsMenu>(GetWorld(), SettingsWidget);

    if (m_SettingsWidgetInst) {
        m_SettingsWidgetInst->SettingsOpen.AddLambda([&](bool SettingsOpen) {
            if (!SettingsOpen) {
                SetVisibility(ESlateVisibility::Visible);
            }
        });
        return true;
    }
    return false;
}

#pragma endregion
#pragma region /// Public Methods ///////////////////////////////////////////////////////////////

void UPauseMenu::PauseGame()
{
    if (m_PlayerController == nullptr) {
        UE_LOG(LogTemp, Error, TEXT("PlayerController is NULL"));
        m_PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    }

    if (!m_PlayerController)
        return;

    FInputModeGameAndUI InputMode;

    AddToViewport();
    m_PlayerController->SetPause(true);
    m_PlayerController->SetInputMode(InputMode);
    m_PlayerController->bShowMouseCursor = true;
}

void UPauseMenu::ResumeGame()
{
    if (!m_PlayerController)
        return;

    FInputModeGameOnly InputMode;

    RemoveFromViewport();
    m_PlayerController->SetInputMode(InputMode);
    m_PlayerController->bShowMouseCursor = false;
    m_PlayerController->SetPause(false);
}

void UPauseMenu::OpenSettings()
{
    SetVisibility(ESlateVisibility::Hidden);

    if (!m_SettingsWidgetInst && !m_PlayerController)
        return;

    m_SettingsWidgetInst->Open();
}

#pragma endregion