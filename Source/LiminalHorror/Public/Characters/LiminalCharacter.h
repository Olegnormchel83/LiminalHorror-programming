// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "LiminalCharacter.generated.h"

class UCameraComponent;
class UGrabber;
class UInputMappingContext;
class UInputAction;
class UPhysicsHandleComponent;
class ALiminalGameModeBase;

UCLASS()
class LIMINALHORROR_API ALiminalCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ALiminalCharacter();

protected:
	virtual void BeginPlay() override;

	void Initialize();

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
	UGrabber* Grabber;

	UPROPERTY(VisibleAnywhere)
	UPhysicsHandleComponent* PhysicsHandle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* MainMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* PickupAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* ChangeGrabberDistanceAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* LockGrabberRotationAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* PauseAction;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY()
	ALiminalGameModeBase* GameMode;

	UPROPERTY()
	APlayerController* PlayerController;

	UFUNCTION()
	void OnGameStateChanged(EGameState State);

	bool bIsRotationLocked = false;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void ChangeGrabberRotation();
	void Grab(const FInputActionValue& Value);
	void Release(const FInputActionValue& Value);
	void ChangeGrabberDistance(const FInputActionValue& Value);
	void LockRotation(const FInputActionValue& Value);
	void UnlockRotation(const FInputActionValue& Value);
	void PauseGame(const FInputActionValue& Value);

};
