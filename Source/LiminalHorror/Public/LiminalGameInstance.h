// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "LiminalGameInstance.generated.h"

UCLASS()
class LIMINALHORROR_API ULiminalGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditdefaultsOnly, Category = Maps, meta = (AllowPrivateAccess = true))
	FName StartupLevelName = NAME_None;

public:
	FORCEINLINE FName GetStartupLevelName() const { return StartupLevelName; }
};
