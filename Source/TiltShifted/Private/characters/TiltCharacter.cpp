#include "characters/TiltCharacter.h"

#include "Blueprint/UserWidget.h"
#include "CineCameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "gui/PauseMenu.h"
#include "gui/SettingsMenu.h"

#pragma region /// Helpers //////////////////////////////////////////////////////////////////////

void ATiltCharacter::DisableEsc()
{
    m_PlayerInputComponent->RemoveActionBinding("Pause", IE_Pressed);
}

void ATiltCharacter::EnableEsc()
{
    m_PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &ATiltCharacter::TogglePause)
        .bExecuteWhenPaused = true;
}

#pragma endregion
#pragma region /// Init /////////////////////////////////////////////////////////////////////////

ATiltCharacter::ATiltCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    AutoPossessPlayer = EAutoReceiveInput::Player0;
    bUseControllerRotationYaw = false;
    AddActorLocalRotation({0.f, -90.f, 0.f});

    const auto mMovementComponent = GetCharacterMovement();
    if (mMovementComponent) {
        mMovementComponent->bOrientRotationToMovement = true;
        mMovementComponent->bUseControllerDesiredRotation = false;
    }

    const auto mCapsuleComponent = GetCapsuleComponent();
    if (mCapsuleComponent) {
        mCapsuleComponent->SetCapsuleHalfHeight(50.f);
        mCapsuleComponent->SetCapsuleRadius(50.f);
    }

    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
    SpringArmComp->SetupAttachment(RootComponent);
    SpringArmComp->AddRelativeRotation({-30.f, 0.f, 0.f});
    SpringArmComp->TargetArmLength = 6000.f;
    SpringArmComp->bUsePawnControlRotation = true;
    SpringArmComp->bInheritPitch = false;
    SpringArmComp->bEnableCameraLag = true;

    CineCameraComp = CreateDefaultSubobject<UCineCameraComponent>(TEXT("CineCameraComponent"));
    CineCameraComp->SetupAttachment(SpringArmComp);
    CineCameraComp->LensSettings.MinFStop = 0.f;
    CineCameraComp->FocusSettings.FocusMethod = ECameraFocusMethod::Manual;
    CineCameraComp->FocusSettings.ManualFocusDistance = 6000.f;
    CineCameraComp->CurrentFocalLength = 50.f;
    CineCameraComp->CurrentAperture = 0.025f;

    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    MeshComp->SetupAttachment(RootComponent);
}

#pragma endregion
#pragma region /// Inputs ///////////////////////////////////////////////////////////////////////

void ATiltCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    m_PlayerInputComponent = PlayerInputComponent;

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

    PlayerInputComponent->BindAxis("MoveForward", this, &ATiltCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ATiltCharacter::MoveRight);

    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnRate", this, &ATiltCharacter::TurnAtRate);
    PlayerInputComponent->BindAxis("LookUpAtRate", this, &ATiltCharacter::LookUpAtRate);

    EnableEsc();
}

void ATiltCharacter::MoveForward(float value)
{
    if ((Controller) && (value != 0.f)) {
        const auto rotation = Controller->GetControlRotation();
        const auto yawRotation = FRotator(0, rotation.Yaw, 0);
        const auto direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);

        AddMovementInput(direction, value);
    }
}

void ATiltCharacter::MoveRight(float value)
{
    if ((Controller) && (value != 0.f)) {
        const auto rotation = Controller->GetControlRotation();
        const auto yawRotation = FRotator(0, rotation.Yaw, 0);
        const auto direction = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

        AddMovementInput(direction, value);
    }
}

void ATiltCharacter::TurnAtRate(float value)
{
    AddControllerYawInput(value * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ATiltCharacter::LookUpAtRate(float value)
{
    AddControllerPitchInput(value * BaseLookUpAtRate * GetWorld()->GetDeltaSeconds());
}

#pragma endregion
#pragma region /// Public Methods ///////////////////////////////////////////////////////////////

void ATiltCharacter::TogglePause()
{
    if (m_PauseMenuWidgetInst == nullptr) {
        UE_LOG(LogTemp, Error, TEXT("PauseMenuWidgetInstance is NULL"));
        m_PauseMenuWidgetInst = CreateWidget<UPauseMenu>(GetWorld(), PauseMenuWidget);

        auto SettingsWidgetInst = m_PauseMenuWidgetInst->GetSettingsWidget();
        if (SettingsWidgetInst) {
            SettingsWidgetInst->SettingsOpen.AddLambda([&](bool SettingsOpen) {
                if (SettingsOpen) {
                    DisableEsc();
                } else {
                    EnableEsc();
                }
            });
        }
    }

    if (m_PlayerController == nullptr) {
        UE_LOG(LogTemp, Error, TEXT("PlayerController is NULL"));
        m_PlayerController = Cast<APlayerController>(GetController());
    }

    if (!m_PauseMenuWidgetInst && !m_PlayerController)
        return;

    if (m_PlayerController->IsPaused()) {
        m_PauseMenuWidgetInst->ResumeGame();
    } else {
        m_PauseMenuWidgetInst->PauseGame();
    }
}

#pragma endregion
