// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "PauseMenu.generated.h"

DECLARE_EVENT(UPauseMenu, MenuResumeEvent);

/**
 *
 */
UCLASS(BlueprintType, Blueprintable)
class TILTSHIFTED_API UPauseMenu : public UUserWidget
{
    GENERATED_BODY()

  public:
    MenuResumeEvent ResumeBtnClicked;

    UFUNCTION(BlueprintCallable, Category = "Gameplay")
    void ResumeGame();

  protected:
};
