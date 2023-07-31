// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Rabbit/Rabbit.h"
#include "WarmthComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RABBITSURVIVAL_API UWarmthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWarmthComponent();

	UFUNCTION(BlueprintCallable)
	float GetWarmth() const { return WarmthOwner->GetRabbitParameters().WarmthStamina; }

protected:
	virtual void BeginPlay() override;
		
private:
	UFUNCTION()
	void WarmthDecrease();

	UFUNCTION()
	void RabbitGotSick();

	UPROPERTY(EditDefaultsOnly, Category = "Warmth", meta = (ClampMin = "0.01", ClampMax = "10.0"))
	float WarmthDecreaseSpeed {1.f};

	UPROPERTY(EditDefaultsOnly, Category = "Warmth", meta = (ClampMin = "0.01", ClampMax = "10.0"))
	float WarmthDecreaseAmount {1.f};

	UPROPERTY(EditDefaultsOnly, Category = "Warmth", meta = (ClampMin = "1.0", ClampMax = "300.0"))
	float TimeBeforeRabbitGetSick {10.f};

	ARabbit* WarmthOwner;

	FTimerHandle WarmthDecreaseTimer;
	FTimerHandle GetSickTimer;
};
