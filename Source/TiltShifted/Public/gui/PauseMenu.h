// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "PauseMenu.generated.h"

class USettingsMenu;

/**
 *
 */
UCLASS(BlueprintType, Blueprintable)
class TILTSHIFTED_API UPauseMenu : public UUserWidget
{
    GENERATED_BODY()

  public:
    UFUNCTION(BlueprintCallable, Category = "Gameplay") void ResumeGame();

    UFUNCTION(BlueprintCallable, Category = "Gameplay")
    void PauseGame();

    UFUNCTION(BlueprintCallable, Category = "Gameplay")
    void OpenSettings();

    USettingsMenu* GetSettingsWidget();

  protected:
    UPROPERTY(EditAnywhere, Category = "UserWidget")
    TSubclassOf<USettingsMenu> SettingsWidget;

  public:
    virtual bool Initialize() override;

  private:
    UPROPERTY()
    USettingsMenu* m_SettingsWidgetInst = nullptr;

    UPROPERTY()
    APlayerController* m_PlayerController = nullptr;
};
