// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "DayNightCycle.generated.h"

class UDirectionalLightComponent;

UCLASS()
class TILTSHIFTED_API ADayNightCycle : public AActor
{
    GENERATED_BODY()

  public:
    ADayNightCycle();

  protected:
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, Category = "Lightings")
    float TurnRate = 1.0f;

  public:
    virtual void Tick(float DeltaTime) override;

  private:
    UPROPERTY()
    UDirectionalLightComponent* LightSource = nullptr;
};
