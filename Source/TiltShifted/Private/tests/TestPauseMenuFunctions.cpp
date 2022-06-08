// Fill out your copyright notice in the Description page of Project Settings.

#include "tests/TestPauseMenuFunctions.h"
#include "Kismet/GameplayStatics.h"
#include "characters/TiltCharacter.h"

void ATestPauseMenuFunctions::BeginPlay()
{
    Super::BeginPlay();

    Player = Cast<ATiltCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

    if (!Player) {
        FinishTest(EFunctionalTestResult::Failed, TEXT("Player null"));
    }

    Player->TogglePause();

    if (GetWorld()->IsPaused()) {
        FinishTest(EFunctionalTestResult::Succeeded, TEXT("World paused!"));

    } else {
        FinishTest(EFunctionalTestResult::Failed, TEXT("World did not paused!"));
    }
}
