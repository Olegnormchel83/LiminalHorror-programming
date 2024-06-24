// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/LiminalGameModeBase.h"

void ALiminalGameModeBase::StartPlay()
{
	Super::StartPlay();

	SetGameState(EGameState::InProgress);
}

bool ALiminalGameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
	const bool PauseSet = Super::SetPause(PC, CanUnpauseDelegate);

	if (PauseSet)
	{
		SetGameState(EGameState::Pause);
	}

	return PauseSet;
}

bool ALiminalGameModeBase::ClearPause()
{
	const bool PauseCleared = Super::ClearPause();

	if (PauseCleared)
	{
		SetGameState(EGameState::InProgress);
	}

	return PauseCleared;
}

void ALiminalGameModeBase::SetGameState(EGameState State)
{
	if (CurrentGameState == State) return;

	CurrentGameState = State;
	GameState.Broadcast(CurrentGameState);
}