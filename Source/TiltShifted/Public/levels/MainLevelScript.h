// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "MainLevelScript.generated.h"

class ADirectionalLight;

/**
 *
 */
UCLASS()
class TILTSHIFTED_API AMainLevelScript : public ALevelScriptActor
{
    GENERATED_BODY()

  public:
    void BeginPlay() override;

  protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lightings")
    float CycleSpeed = 30.f;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Lightings")
    ADirectionalLight* Sun = nullptr;

  private:
    UFUNCTION()
    void RotateSun();
};
