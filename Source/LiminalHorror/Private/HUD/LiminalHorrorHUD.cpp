// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/LiminalHorrorHUD.h"

#include "Blueprint/UserWidget.h"
#include "GameModes/LiminalGameModeBase.h"

void ALiminalHorrorHUD::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* Controller = GetWorld()->GetFirstPlayerController();
	PauseWidget = CreateWidget<UUserWidget>(Controller, PauseWidgetClass);
	if (Controller && PauseWidget)
	{
		PauseWidget->AddToViewport();
		PauseWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	ALiminalGameModeBase* GameMode = Cast<ALiminalGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->GameState.AddUObject(this, &ALiminalHorrorHUD::OnGameStateChanged);
	}
}

void ALiminalHorrorHUD::OnGameStateChanged(EGameState State)
{
	if (State == EGameState::Pause)
	{
		PauseWidget->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		PauseWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}