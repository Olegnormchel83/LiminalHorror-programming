// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LiminalCoreTypes.h"
#include "LiminalGameModeBase.generated.h"


UCLASS()
class LIMINALHORROR_API ALiminalGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void StartPlay() override;
	virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;
	virtual bool ClearPause() override;

	FGameStateSignature GameState;

private:
	EGameState CurrentGameState = EGameState::WaitingToStart;

	void SetGameState(EGameState State);
};
