// Copyright Epic Games, Inc. All Rights Reserved.

#include "RabbitSurvivalGameMode.h"
#include "RabbitSurvivalCharacter.h"
#include "PlayerController/BasePlayerController.h"
#include "UObject/ConstructorHelpers.h"

ARabbitSurvivalGameMode::ARabbitSurvivalGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		PlayerControllerClass = ABasePlayerController::StaticClass();
	}
}
