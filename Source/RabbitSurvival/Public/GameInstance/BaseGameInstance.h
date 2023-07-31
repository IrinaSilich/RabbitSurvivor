// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BaseGameInstance.generated.h"

UCLASS()
class RABBITSURVIVAL_API UBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	virtual void Init() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Save system")
	FString SaveSlot = "SavedGame";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Save system", meta = (ClampMin = "30.0", ClampMax = "300.0"))
	float SaveGameInterval {30.f};
};
