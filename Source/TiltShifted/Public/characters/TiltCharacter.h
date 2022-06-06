// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TiltCharacter.generated.h"

class USpringArmComponent;
class UCineCameraComponent;
class UStaticMeshComponent;
class UCharacterMovementComponent;
class UPauseMenu;

UCLASS()
class TILTSHIFTED_API ATiltCharacter : public ACharacter
{
    GENERATED_BODY()

  public:
    // Sets default values for this character's properties
    ATiltCharacter();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    USpringArmComponent* SpringArmComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    UCineCameraComponent* CineCameraComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player")
    UStaticMeshComponent* MeshComp;

    UPROPERTY(EditAnywhere, Category = "UserWidget")
    TSubclassOf<UPauseMenu> PauseMenuWidget;

    UFUNCTION(BlueprintCallable, Category = "Gameplay")
    void TogglePause();

  protected:
    void MoveForward(float value);
    void MoveRight(float value);
    void TurnAtRate(float value);
    void LookUpAtRate(float value);
    void DisableEsc();
    void EnableEsc();

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
    float BaseTurnRate = 45.f;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
    float BaseLookUpAtRate = 45.f;

  public:
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

  private:
    UPROPERTY()
    UPauseMenu* m_PauseMenuWidgetInst = nullptr;

    UPROPERTY()
    APlayerController* m_PlayerController = nullptr;

    UPROPERTY()
    UInputComponent* m_PlayerInputComponent = nullptr;
};
