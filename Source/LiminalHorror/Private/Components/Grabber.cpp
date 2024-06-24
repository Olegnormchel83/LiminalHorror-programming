// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Grabber.h"

#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Kismet/KismetMathLibrary.h"

UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	HoldDistance = MaxHoldDistance / 2;
}


void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicsHandle && PhysicsHandle->GetGrabbedComponent() /*&& !bIsLocked*/)
	{
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());

	}
}

void UGrabber::Release()
{
	if (!PhysicsHandle) return;

	if (PhysicsHandle->GetGrabbedComponent())
	{
		PhysicsHandle->ReleaseComponent();
		HoldDistance = MaxHoldDistance / 2;
	}
}

void UGrabber::Grab()
{
	if (!PhysicsHandle) return;

	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDistance;

	FHitResult HitResult;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius);
	bool HasHit = GetWorld()->SweepSingleByChannel(HitResult, Start, End, FQuat::Identity, ECC_GameTraceChannel1, Sphere);
	if (HasHit)
	{
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		HitComponent->WakeAllRigidBodies();

		PhysicsHandle->GrabComponentAtLocationWithRotation(HitResult.GetComponent(), NAME_None, HitResult.GetActor()->GetActorLocation(), GetComponentRotation());
	}
}

void UGrabber::SetHoldDistance(const float Value)
{
	HoldDistance = FMath::Clamp(HoldDistance + ChangeDistance * Value, MinHoldDistance, MaxHoldDistance);
}

void UGrabber::SetRotationOffset(const FRotator MouseRotation)
{
	//if (bIsLocked)
	//{

	//	RotationOffset = MouseRotation;
	//	PhysicsHandle->SetTargetRotation(MouseRotation);
	//}
	RotationOffset = MouseRotation;
	//PhysicsHandle->SetTargetRotation(MouseRotation + GetComponentRotation());
}

