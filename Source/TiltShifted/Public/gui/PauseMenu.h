// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "PauseMenu.generated.h"

class USettingsMenu;

DECLARE_EVENT_OneParam(UPauseMenu, SettingsBtnEvent, bool);

/**
 *
 */
UCLASS(BlueprintType, Blueprintable)
class TILTSHIFTED_API UPauseMenu : public UUserWidget
{
    GENERATED_BODY()

  public:
    SettingsBtnEvent SettingsToggled;

  public:
    UFUNCTION(BlueprintCallable, Category = "Gameplay") void ResumeGame();

    UFUNCTION(BlueprintCallable, Category = "Gameplay")
    void PauseGame();

    UFUNCTION(BlueprintCallable, Category = "Gameplay")
    void OpenSettings();

  protected:
    UPROPERTY(EditAnywhere, Category = "UserWidget")
    TSubclassOf<USettingsMenu> SettingsWidget;

  private:
    USettingsMenu* m_SettingsWidgetInst;
    APlayerController* m_PlayerController;

    void checkPlayerController();
};
