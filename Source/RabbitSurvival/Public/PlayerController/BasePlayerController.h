// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

class ARabbit;

UCLASS()
class RABBITSURVIVAL_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ARabbit* GetFrozenRabbit() const { return FrozenRabbit; };

protected:
	virtual void BeginPlay() override;

	void SetPlayerView();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Rabbit Referencies")
	ARabbit* FrozenRabbit;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player View")
	TSubclassOf<AActor> CameraView;
};
