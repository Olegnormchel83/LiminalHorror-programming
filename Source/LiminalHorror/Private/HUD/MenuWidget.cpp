// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/MenuWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "LiminalGameInstance.h"

void UMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	MenuSetup();
}

void UMenuWidget::MenuSetup()
{
	if (GetWorld())
	{
		APlayerController* Controller = GetWorld()->GetFirstPlayerController();
		if (Controller)
		{
			Controller->SetInputMode(FInputModeUIOnly());
			Controller->SetShowMouseCursor(true);
		}
	}

	if (StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &UMenuWidget::OnStartGame);
	}

	if (ExitButton)
	{
		ExitButton->OnClicked.AddDynamic(this, &UMenuWidget::OnEndGame);
	}
}

void UMenuWidget::OnStartGame()
{
	if (!GetWorld()) return;
	const ULiminalGameInstance* GameInstance = GetWorld()->GetGameInstance<ULiminalGameInstance>();
	if (GameInstance && !GameInstance->GetStartupLevelName().IsNone())
	{

		UGameplayStatics::OpenLevel(this, GameInstance->GetStartupLevelName());
	}
}

void UMenuWidget::OnEndGame()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}