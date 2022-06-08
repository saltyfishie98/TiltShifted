// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FunctionalTest.h"
#include "TestPauseMenuFunctions.generated.h"

/**
 *
 */
UCLASS()
class TILTSHIFTED_API ATestPauseMenuFunctions : public AFunctionalTest
{
    GENERATED_BODY()
  private:
    UPROPERTY()
    class ATiltCharacter* Player;

  protected:
    virtual void BeginPlay() override;
};
