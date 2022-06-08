// Fill out your copyright notice in the Description page of Project Settings.

#include "levels/MainLevelScript.h"
#include "Engine/DirectionalLight.h"

void AMainLevelScript::BeginPlay()
{
    Super::BeginPlay();

    FTimerHandle handle;
    GetWorld()->GetTimerManager().SetTimer(handle, this, &AMainLevelScript::RotateSun, 0.01f, true);
}

void AMainLevelScript::RotateSun()
{
    if (!Sun)
        return;

    auto DeltaTime = GetWorld()->GetDeltaSeconds();

    Sun->AddActorLocalRotation(FRotator((DeltaTime * CycleSpeed), 0, 0));
}
