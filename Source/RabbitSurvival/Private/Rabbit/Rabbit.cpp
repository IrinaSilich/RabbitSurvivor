// Fill out your copyright notice in the Description page of Project Settings.


#include "Rabbit/Rabbit.h"
#include "Components/WarmthComponent.h"
#include "FoodSpot/FoodSpot.h"

ARabbit::ARabbit()
{
	PrimaryActorTick.bCanEverTick = false;
	
	WarmthComponent = CreateDefaultSubobject<UWarmthComponent>("WarmthComponent");
}

void ARabbit::BeginPlay()
{
	Super::BeginPlay();

	if (GameConstProperties)
	{
		PropertiesRowNames = GameConstProperties->GetRowNames();

		if (PropertiesRowNames.IsValidIndex(0))
		{
			PropertiesRow = GameConstProperties->FindRow<FGameConstProperties>(PropertiesRowNames[0], "");
		}
	}
}

void ARabbit::CancelFoodCollection()
{
	if (!RabbitParameters.AssignedFoodSpot || !PropertiesRow)
	{
		return;
	}

	RabbitParameters.AssignedFoodSpot->ActivateSeatWhenFoodCollectionCancelled(RabbitParameters.AssignedCollectionSeat);

	bool ToFreezeOrNotToFreeze = FMath::RandBool();

	if (RabbitResources.CurrentAmount < PropertiesRow->MinAmountFoodCollectedNotToFreeze && ToFreezeOrNotToFreeze)
	{
		FTimerHandle FreezeRabbit;
		GetWorldTimerManager().SetTimer(FreezeRabbit, this, &ARabbit::FreezeRabbit, PropertiesRow->TimeBeforeSentToHoleRabbitFreezes, false);
	}

	RabbitParameters.AssignedFoodSpot->DecreaseRabbitsAssigned(this);
	RabbitParameters.AssignedFoodSpot->SetRabbitFreezingRate();

	RabbitParameters.TaskAssigned = RabbitActivity::None;
	RabbitParameters.IsTaskProcessed = false;
	RabbitParameters.AssignedFoodSpot = nullptr;
	RabbitParameters.AssignedCollectionSeat = nullptr;
}

void ARabbit::RabbitIsFrozen() 
{
	OnRabbitFrozen.Broadcast();
}

void ARabbit::RabbitIsSick()
{
	OnRabbitGotSick.Broadcast();
}

void ARabbit::FreezeRabbit()
{
	RabbitParameters.WarmthStamina = 0.f;
	RabbitParameters.IsFrozen = true;
	RabbitResources.CurrentAmount = 0.f;
	RabbitIsFrozen();
}