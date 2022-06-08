// Fill out your copyright notice in the Description page of Project Settings.

#include "lightings/DayNightCycle.h"
#include "Components/DirectionalLightComponent.h"

// Sets default values
ADayNightCycle::ADayNightCycle()
{
    PrimaryActorTick.bCanEverTick = true;
    LightSource = CreateDefaultSubobject<UDirectionalLightComponent>(TEXT("SunLight"));
}

void ADayNightCycle::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ADayNightCycle::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (LightSource) {
        AddActorLocalRotation(FRotator((DeltaTime * TurnRate), 0, 0));
    }
}
