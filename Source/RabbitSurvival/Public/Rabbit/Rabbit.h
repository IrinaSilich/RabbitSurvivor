// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Auxiliaries/RabbitUtilities.h"
#include "Kismet/GameplayStatics.h"
#include "Rabbit.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnRabbitFrozen);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRabbitGotSick);

class UWarmthComponent;

USTRUCT(BlueprintType)
struct FWarmthDecreaseRates
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "1.0", ClampMax = "10.0"))
	float ForOneRabbitByBush {10.f};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "1.0", ClampMax = "10.0"))
	float ForTwoRabbitsByBush {8.f};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "1.0", ClampMax = "10.0"))
	float ForThreeRabbitsByBush {2.f};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "1.0", ClampMax = "10.0"))
	float ForFourRabbitsByBush {1.f};
};

UCLASS()
class RABBITSURVIVAL_API ARabbit : public ACharacter
{
	GENERATED_BODY()

public:
	ARabbit();

	UFUNCTION(BlueprintCallable)
	void SetRabbitParameters(FRabbitParameters SpawnedRabbitParameters) { RabbitParameters = SpawnedRabbitParameters; };

	UFUNCTION(BlueprintCallable)
	void SetRabbitResources(FRabbitResourceCollection SpawnedRabbitResources) { RabbitResources = SpawnedRabbitResources; }

	UFUNCTION(BlueprintCallable)
	FRabbitParameters GetRabbitParameters() const { return RabbitParameters; };

	UFUNCTION(BlueprintCallable)
	FRabbitResourceCollection GetRabbitResources() const { return RabbitResources; };

	void RabbitIsFrozen();
	void RabbitIsSick();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Warmth Component")
	FWarmthDecreaseRates WarmthDecreaseRates;

	float WarmthDecreaseCurrentRate {1.f};

	FOnRabbitFrozen OnRabbitFrozen;

	UPROPERTY(BlueprintAssignable)
	FOnRabbitGotSick OnRabbitGotSick;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void CancelFoodCollection();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UWarmthComponent* WarmthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Rabbit Data")
	FRabbitParameters RabbitParameters;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Rabbit Data")
	FRabbitResourceCollection RabbitResources;

private:
	UFUNCTION()
	void FreezeRabbit();

	UPROPERTY(EditDefaultsOnly, Category = "Const Properties")
	UDataTable* GameConstProperties;

	FGameConstProperties* PropertiesRow;

	TArray<FName> PropertiesRowNames;
};
