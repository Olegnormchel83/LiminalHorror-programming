// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/PauseWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"

void UPauseWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	PauseSetup();
}

void UPauseWidget::PauseSetup()
{
	if (ResumeButton)
	{
		ResumeButton->OnClicked.AddDynamic(this, &UPauseWidget::OnResumeGame);
	}

	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &UPauseWidget::OnEndGame);
	}
}

void UPauseWidget::OnResumeGame()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->ClearPause();
}

void UPauseWidget::OnEndGame()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}