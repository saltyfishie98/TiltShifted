// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "SettingsMenu.generated.h"

DECLARE_EVENT_OneParam(USettingsMenu, SettingsBtnEvent, bool);

/**
 *
 */
UCLASS(BlueprintType, Blueprintable)
class TILTSHIFTED_API USettingsMenu : public UUserWidget
{
    GENERATED_BODY()

  public:
    SettingsBtnEvent SettingsOpen;

    UFUNCTION(BlueprintCallable, Category = "Gameplay")
    void Open();

    UFUNCTION(BlueprintCallable, Category = "Gameplay")
    void Close();
};
