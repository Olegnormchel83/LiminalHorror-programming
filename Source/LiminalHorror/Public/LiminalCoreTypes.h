#pragma once

#include "LiminalCoreTypes.generated.h"

UENUM(BlueprintType)
enum class EGameState : uint8
{
	InProgress = 0,
	WaitingToStart,
	Pause,
};

DECLARE_MULTICAST_DELEGATE_OneParam(FGameStateSignature, EGameState); 
