// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Grabber.generated.h"

class UPhysicsHandleComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LIMINALHORROR_API UGrabber : public USceneComponent
{
	GENERATED_BODY()

public:	
	UGrabber();

	void SetHoldDistance(const float Value);
	void SetRotationOffset(const FRotator MouseRotation);
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float MaxGrabDistance = 400.0f;

	UPROPERTY(EditAnywhere)
	float GrabRadius = 100.0f;

	UPROPERTY(EditAnywhere)
	float MaxHoldDistance = 200.0f;

	UPROPERTY(EditAnywhere)
	float MinHoldDistance = 80.0f;

	UPROPERTY(EditAnywhere)
	float ChangeDistance = 10.0f;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Release();
	void Grab();

private:
	UPROPERTY()
	UPhysicsHandleComponent* PhysicsHandle;

	float HoldDistance;

	bool bIsLocked = false;
	FRotator RotationOffset;

public:
	FORCEINLINE void SetLock(const bool IsLocked) { bIsLocked = IsLocked; }
	FORCEINLINE void SetRotationOffsetZero() { RotationOffset = FRotator(0.0f, 0.0f, 0.0f); }
};
