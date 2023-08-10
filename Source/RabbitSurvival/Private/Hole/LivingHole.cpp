// Fill out your copyright notice in the Description page of Project Settings.

#include "Hole/LivingHole.h"
#include "Auxiliaries/RabbitUtilities.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ALivingHole::ALivingHole()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ALivingHole::BeginPlay()
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

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ALivingHole::OnLivingHoleOverlap);

	GetWorldTimerManager().SetTimer(WarmUpTimer, this, &ALivingHole::WarmingUpRabbits, WarmUpTimerInterval, true);
	GetWorldTimerManager().SetTimer(HealCheckTimer, this, &ALivingHole::SetUpHealing, HealCheckTimerInterval, true);
}

void ALivingHole::InitHole()
{
	if (!PropertiesRow)
	{
		return;
	}

	for (int32 i = 0; i < PropertiesRow->RabbitsCountOnStart; i++)
	{
		RabbitsParameters.Add(StartParameters);
	}

	TotalRabbitsCount = PropertiesRow->RabbitsCountOnStart;
}

void ALivingHole::CheckForFrozenRabbitsInGeneralSection()
{
	if (!RabbitsParameters.IsEmpty())
	{
		for (int32 i = 0; i < RabbitsParameters.Num(); i++)
		{
			if (RabbitsParameters[i].IsFrozen == true)
			{
				WarmedUpRabbitsParameters.Add(RabbitsParameters[i]);
				RabbitsParameters.RemoveAt(i);
			}
		}
	}
}

ARabbit* ALivingHole::SpawnRabbit(RabbitActivity AssignedTask, AFoodSpot* AssignedFoodSpot, USceneComponent* AssignedCollectionSpot)
{
	UWorld* World = GetWorld();

	if (World && !RabbitsParameters.IsEmpty())
	{
		RabbitsParameters[0].TaskAssigned = AssignedTask;
		RabbitsParameters[0].AssignedFoodSpot = AssignedFoodSpot;
		RabbitsParameters[0].AssignedCollectionSeat = AssignedCollectionSpot;

		FTransform SpawnTransform = this->GetActorTransform();

		SpawnedRabbit = World->SpawnActorDeferred<ARabbit>(RabbitClass, SpawnTransform, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);

		if (SpawnedRabbit)
		{
			SpawnedRabbit->OnRabbitFrozen.AddUObject(this, &ALivingHole::TellGameModeRabbitIsFrozen);
			SpawnedRabbit->OnRabbitGotSick.AddDynamic(this, &ALivingHole::TellGameModeRabbitIsSick);
			SpawnedRabbit->SetRabbitParameters(RabbitsParameters[0]);
			SpawnedRabbit->FinishSpawning(SpawnTransform);

			RabbitsOutsideHole.Add(SpawnedRabbit);

			RabbitsParameters.RemoveAt(0);
		}
	}

	return SpawnedRabbit;
}

void ALivingHole::RemoveRabbit(ARabbit* RabbitToRemove)
{
	if (!RabbitToRemove)
	{
		return;
	}

	if (RabbitToRemove->GetRabbitParameters().TaskAssigned == RabbitActivity::None || RabbitToRemove->GetRabbitParameters().TaskAssigned == RabbitActivity::Rescue)
	{
		if (RabbitToRemove->GetRabbitParameters().TaskAssigned == RabbitActivity::Rescue)
		{
			FRabbitParameters RemovedRabbitParameters = RabbitToRemove->GetRabbitParameters();
			RemovedRabbitParameters.TaskAssigned = RabbitActivity::None;
			RabbitToRemove->SetRabbitParameters(RemovedRabbitParameters);
		}
		
		RabbitsParameters.Add(RabbitToRemove->GetRabbitParameters());
		RabbitToRemove->Destroy();

		RabbitsOutsideHole.Remove(RabbitToRemove);

		GetWorldTimerManager().SetTimer(WarmUpTimer, this, &ALivingHole::WarmingUpRabbits, WarmUpTimerInterval, true);
	}
	else if (RabbitToRemove->GetRabbitParameters().TaskAssigned == RabbitActivity::WarmUp)
	{
		WarmedUpRabbitsParameters.Add(RabbitToRemove->GetRabbitParameters());
		RabbitToRemove->Destroy();
		GetWorldTimerManager().SetTimer(WarmUpTimer, this, &ALivingHole::WarmingUpRabbits, WarmUpTimerInterval, true);
	}
	else if (RabbitToRemove->GetRabbitParameters().TaskAssigned == RabbitActivity::Treated)
	{
		HospitalizedRabbitsParameters.Add(RabbitToRemove->GetRabbitParameters());
		RabbitToRemove->Destroy();
	}
}

void ALivingHole::WarmingUpRabbits()
{
	if (!WarmedUpRabbitsParameters.IsEmpty())
	{
		for (int32 i = 0; i < WarmedUpRabbitsParameters.Num(); i++)
		{
			WarmedUpRabbitsParameters[i].WarmthStamina = FMath::Clamp(WarmedUpRabbitsParameters[i].WarmthStamina + WarmUpAmountPerInterval, 0.f, 100.f);

			if (WarmedUpRabbitsParameters[i].WarmthStamina >= 100.f)
			{
				RabbitsParameters.Add(WarmedUpRabbitsParameters[i]);
				WarmedUpRabbitsParameters.RemoveAt(i);
				OnDecreaseFrozenRabbitsCount.Broadcast();
			}
		}
	}

	if (!RabbitsParameters.IsEmpty())
	{
		for (int32 i = 0; i < RabbitsParameters.Num(); i++)
		{
			if (RabbitsParameters[i].TaskAssigned == RabbitActivity::None)
			{
				RabbitsParameters[i].WarmthStamina = FMath::Clamp(RabbitsParameters[i].WarmthStamina + WarmUpAmountPerInterval * HoleWarmUpCoefficient, 0.f, 100.f);
			}
			else if (RabbitsParameters[i].TaskAssigned == RabbitActivity::Breed)
			{
				RabbitsParameters[i].WarmthStamina = FMath::Clamp(RabbitsParameters[i].WarmthStamina + WarmUpAmountPerInterval * BreedRoomWarmUpCoefficient, 0.f, 100.f);
			}
		}
	}

	if (WarmedUpRabbitsParameters.IsEmpty() && RabbitsParameters.IsEmpty() && GetWorldTimerManager().IsTimerActive(WarmUpTimer))
	{
		GetWorldTimerManager().ClearTimer(WarmUpTimer);
	}
}

void ALivingHole::SetUpHealing()
{
	if (!PropertiesRow || !IfEnoughFoodForOneHeal() || HospitalizedRabbitsParameters.IsEmpty())
	{
		return;
	}

	int32 HowManyRabbitsCanBeTreated = FoodAmountCollected / PropertiesRow->FoodAmountForOneHeal;

	if (HowManyRabbitsCanBeTreated >= HospitalizedRabbitsParameters.Num())
	{
		for (int32 i = 0; i < HospitalizedRabbitsParameters.Num(); i++)
		{
			TreatedRabbitsParameters.Add(HospitalizedRabbitsParameters[i]);
			FoodAmountCollected = FoodAmountCollected - PropertiesRow->FoodAmountForOneHeal;
		}

		HospitalizedRabbitsParameters.Empty();
	}
	else
	{
		for (int32 i = 0; i < HowManyRabbitsCanBeTreated; i++)
		{
			TreatedRabbitsParameters.Add(HospitalizedRabbitsParameters[i]);
			HospitalizedRabbitsParameters.RemoveAt(i);
			FoodAmountCollected = FoodAmountCollected - PropertiesRow->FoodAmountForOneHeal;
		}
	}

	if (!GetWorldTimerManager().IsTimerActive(HealTimer))
	{
		GetWorldTimerManager().SetTimer(HealTimer, this, &ALivingHole::HealingRabbits, HealTimerInterval, true);
	}
}

void ALivingHole::HealingRabbits()
{
	if (!TreatedRabbitsParameters.IsEmpty())
	{
		for (int32 i = 0; i < TreatedRabbitsParameters.Num(); i++)
		{
			TreatedRabbitsParameters[i].WarmthStamina = FMath::Clamp(TreatedRabbitsParameters[i].WarmthStamina + HealAmountPerInterval, 0.f, 100.f);

			if (TreatedRabbitsParameters[i].WarmthStamina >= 100.f)
			{
				RabbitsParameters.Add(TreatedRabbitsParameters[i]);
				TreatedRabbitsParameters.RemoveAt(i);
				OnDecreaseFrozenRabbitsCount.Broadcast();
				OnDecreaseSickRabbitsCount.Broadcast();
			}
		}
	}
	else
	{
		GetWorldTimerManager().ClearTimer(HealTimer);
	}
}

bool ALivingHole::IfEnoughFoodForOneBreed() const
{
	if (PropertiesRow)
	{
		return FoodAmountCollected >= PropertiesRow->FoodAmountForOneBreed ? true : false;
	}

	return false;
}

bool ALivingHole::IfEnoughFoodForOneHeal() const
{
	if (PropertiesRow)
	{
		return FoodAmountCollected >= PropertiesRow->FoodAmountForOneHeal ? true : false;
	}

	return false;
}

void ALivingHole::CheckForFoodAndPairRabbitsToBreed()
{
	if (!PropertiesRow || !IfEnoughFoodForOneBreed() || TotalRabbitsCount >= PropertiesRow->MaxRabbitsOnLevel || RabbitsParameters.IsEmpty())
	{
		return;
	}

	for (int32 i = 0; i < RabbitsParameters.Num(); i++)
	{
		RabbitsParameters[i].TaskAssigned = RabbitActivity::Breed;
		BreedRabbitsParameters.Add(RabbitsParameters[i]);
		RabbitsParameters.RemoveAt(i);

		if (BreedRabbitsParameters.Num() == 2)
		{
			FoodAmountCollected = FoodAmountCollected - PropertiesRow->FoodAmountForOneBreed;
			BreedNewRabbit();
			break;
		}
		else
		{
			continue;
		}
	}
}

void ALivingHole::OnLivingHoleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ARabbit* RabbitOverlapped = Cast<ARabbit>(OtherActor);

	if (RabbitOverlapped)
	{
		FoodAmountCollected = FoodAmountCollected + RabbitOverlapped->GetRabbitResources().CurrentAmount;
		FRabbitResourceCollection OverlappedRabbitResources = RabbitOverlapped->GetRabbitResources();
		OverlappedRabbitResources.CurrentAmount = 0.f;
		RabbitOverlapped->SetRabbitResources(OverlappedRabbitResources);
	}
}

void ALivingHole::BreedNewRabbit()
{
	if (!PropertiesRow)
	{
		return;
	}

	GetWorldTimerManager().SetTimer(BreedRabbitTimer, this, &ALivingHole::NewRabbitsBorn, PropertiesRow->TimeBeforeRabbitBorn, false);
}

void ALivingHole::NewRabbitsBorn()
{
	if (!PropertiesRow)
	{
		return;
	}

	int32 NewBornRabbitsCount = UKismetMathLibrary::RandomIntegerInRange(PropertiesRow->MinNewBornRabbitsCount, PropertiesRow->MaxNewBornRabbitsCount);

	int32 MaxRabbitsOnLevel {PropertiesRow->MaxRabbitsOnLevel};

	if (NewBornRabbitsCount + TotalRabbitsCount > MaxRabbitsOnLevel)
	{
		NewBornRabbitsCount = MaxRabbitsOnLevel - TotalRabbitsCount;
	}

	TotalRabbitsCount = TotalRabbitsCount + NewBornRabbitsCount;

	for (int32 i = 0; i < NewBornRabbitsCount; i++)
	{
		RabbitsParameters.Add(StartParameters);
	}

	if (BreedRabbitTimer.IsValid())
	{
		GetWorldTimerManager().ClearTimer(BreedRabbitTimer);
	}

	for (int32 i = 0; i < BreedRabbitsParameters.Num(); i++)
	{
		BreedRabbitsParameters[i].TaskAssigned = RabbitActivity::None;
		RabbitsParameters.Add(BreedRabbitsParameters[i]);
	}

	BreedRabbitsParameters.Empty();
	
	OnRabbitsCountChanged.Broadcast();
}

void ALivingHole::TellGameModeRabbitIsFrozen()
{
	OnIncreaseFrozenRabbitsCount.Broadcast();
}

void ALivingHole::TellGameModeRabbitIsSick()
{
	OnIncreaseSickRabbitsCount.Broadcast();
}