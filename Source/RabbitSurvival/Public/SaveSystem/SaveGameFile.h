// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Auxiliaries/RabbitUtilities.h"
#include "SaveGameFile.generated.h"

UCLASS()
class RABBITSURVIVAL_API USaveGameFile : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	TArray<FRabbitParameters> SavedRabbitsParameters;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	TArray<FRabbitParameters> SavedWarmingUpRabbitsParameters;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	float SavedFoodAmountCollected;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite)
	int32 SavedTotalRabbitsCount;
};
