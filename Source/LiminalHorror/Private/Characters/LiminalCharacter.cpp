// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/LiminalCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/Grabber.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "GameFramework/PlayerController.h"

#include "GameModes/LiminalGameModeBase.h"

ALiminalCharacter::ALiminalCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetRootComponent());

	Grabber = CreateDefaultSubobject<UGrabber>(TEXT("Grabber"));
	Grabber->SetupAttachment(Camera);

	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));
}

void ALiminalCharacter::BeginPlay()
{
	Super::BeginPlay();


	Initialize();

}

void ALiminalCharacter::Initialize()
{
	PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MainMappingContext, 0);
		}
	}

	GameMode = Cast<ALiminalGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->GameState.AddUObject(this, &ALiminalCharacter::OnGameStateChanged);
	}
}

void ALiminalCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ALiminalCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{

		////Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ALiminalCharacter::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ALiminalCharacter::Look);

		// Pickuping
		EnhancedInputComponent->BindAction(PickupAction, ETriggerEvent::Started, this, &ALiminalCharacter::Grab);
		EnhancedInputComponent->BindAction(PickupAction, ETriggerEvent::Completed, this, &ALiminalCharacter::Release);

		// Change Grab Distance
		EnhancedInputComponent->BindAction(ChangeGrabberDistanceAction, ETriggerEvent::Triggered, this, &ALiminalCharacter::ChangeGrabberDistance);

		// LockRotation
		EnhancedInputComponent->BindAction(LockGrabberRotationAction, ETriggerEvent::Started, this, &ALiminalCharacter::LockRotation);
		EnhancedInputComponent->BindAction(LockGrabberRotationAction, ETriggerEvent::Completed, this, &ALiminalCharacter::UnlockRotation);

		// Pause
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &ALiminalCharacter::PauseGame);
	}

}

void ALiminalCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ALiminalCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	if (!Controller) return;

	if (!bIsRotationLocked || !PhysicsHandle->GetGrabbedComponent())
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
	else
	{
		ChangeGrabberRotation();
	}
}

void ALiminalCharacter::ChangeGrabberRotation()
{
	double X, Y;
	if (GetWorld()->GetFirstPlayerController()->GetMousePosition(X, Y))
	{
		Grabber->SetRotationOffset(FRotator(Y * 0.05, X * 0.05, 0.0f));
	}
}

void ALiminalCharacter::Grab(const FInputActionValue& Value)
{
	Grabber->Grab();
}

void ALiminalCharacter::Release(const FInputActionValue& Value)
{
	Grabber->Release();
	Grabber->SetRotationOffsetZero();
}

void ALiminalCharacter::ChangeGrabberDistance(const FInputActionValue& Value)
{
	if (bIsRotationLocked) return;

	float Vl = Value.Get<float>();
	Grabber->SetHoldDistance(Vl);
}

void ALiminalCharacter::LockRotation(const FInputActionValue& Value)
{
	Grabber->SetLock(bIsRotationLocked = true);
}

void ALiminalCharacter::UnlockRotation(const FInputActionValue& Value)
{
	Grabber->SetLock(bIsRotationLocked = false);
}

void ALiminalCharacter::PauseGame(const FInputActionValue& Value)
{
	//GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Green, FString(TEXT("Paused")));
	if (!GetWorld() || !GameMode) return;

	if (GameMode->IsPaused())
	{
		GameMode->ClearPause();
	}
	else
	{
		GameMode->SetPause(PlayerController);
	}
}

void ALiminalCharacter::OnGameStateChanged(EGameState State)
{
	if (State == EGameState::InProgress)
	{
		PlayerController->SetInputMode(FInputModeGameOnly());
		PlayerController->bShowMouseCursor = false;
	}
	else if (State == EGameState::Pause)
	{
		PlayerController->SetInputMode(FInputModeGameAndUI());
		PlayerController->bShowMouseCursor = true;
	}
	else
	{
		PlayerController->SetInputMode(FInputModeUIOnly());
		PlayerController->bShowMouseCursor = true;
	}
}
