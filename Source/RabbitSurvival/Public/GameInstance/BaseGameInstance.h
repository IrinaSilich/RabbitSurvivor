// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BaseGameInstance.generated.h"

class ALivingHole;

UCLASS()
class RABBITSURVIVAL_API UBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	virtual void Init() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Save System")
	FString SaveSlot = "SavedGame";

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Save System", meta = (ClampMin = "30.0", ClampMax = "300.0"))
	float SaveGameInterval {30.f};

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Game Entities")
	ALivingHole* LivingHole;
};
