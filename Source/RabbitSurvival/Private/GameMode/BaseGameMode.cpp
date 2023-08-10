// Fill out your copyright notice in the Description page of Project Settings.

#include "GameMode/BaseGameMode.h"
#include "Auxiliaries/RabbitUtilities.h"
#include "PlayerController/BasePlayerController.h"

ABaseGameMode::ABaseGameMode()
{
	PlayerControllerClass = ABasePlayerController::StaticClass();
}

void ABaseGameMode::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle InitTimer;
	GetWorldTimerManager().SetTimer(InitTimer, this, &ABaseGameMode::InitGameMode, InitDelay, false);

	CollectorRowNames = RabbitsCollectorEventsData->GetRowNames();

	GetCollectorGurrentRow(CollectorCurrentRowIndex);
}

void ABaseGameMode::InitGameMode()
{
	LivingHole = Cast<ALivingHole>(UGameplayStatics::GetActorOfClass(GetWorld(), LivingHoleClass));

	if (LivingHole)
	{
		LivingHole->OnIncreaseFrozenRabbitsCount.AddUObject(this, &ABaseGameMode::IncreaseFrozenRabbitsCount);
		LivingHole->OnDecreaseFrozenRabbitsCount.AddUObject(this, &ABaseGameMode::DecreaseFrozenRabbitsCount);
		LivingHole->OnIncreaseSickRabbitsCount.AddUObject(this, &ABaseGameMode::IncreaseSickRabbitsCount);
		LivingHole->OnDecreaseSickRabbitsCount.AddUObject(this, &ABaseGameMode::DecreaseSickRabbitsCount);
	}

	SetHoleAndLaunchSaves();
}

void ABaseGameMode::GetCollectorGurrentRow(int32 CollectorRowIndex)
{
	if (CollectorRowNames.IsValidIndex(CollectorRowIndex))
	{
		CollectorCurrentRow = RabbitsCollectorEventsData->FindRow<FRabbitsCollectorEventsData>(CollectorRowNames[CollectorRowIndex], "");
	}

	if (CollectorCurrentRow)
	{
		GetWorldTimerManager().SetTimer(CollectionTimer, this, &ABaseGameMode::SomeoneHasComeForRabbits, CollectorCurrentRow->TimeBeforeEventHappens, false);
	}
}

void ABaseGameMode::SomeoneHasComeForRabbits()
{
	if (CollectorCurrentRowIndex < CollectorRowNames.Num())
	{
		RabbitsAreTaken(CollectorCurrentRowIndex);
		CollectorCurrentRowIndex++;
		OnCollectorRowIndexChanged.Broadcast(CollectorCurrentRowIndex);
	}
}

void ABaseGameMode::IncreaseFrozenRabbitsCount()
{
	FrozenRabbitsCount++;
	
	UE_LOG(LogTemp, Error, TEXT("Total: %i, Frozen: %i"), LivingHole->TotalRabbitsCount, FrozenRabbitsCount);

	if (LivingHole->TotalRabbitsCount == FrozenRabbitsCount)
	{
		GameOver();
	}
}

void ABaseGameMode::DecreaseFrozenRabbitsCount()
{
	FrozenRabbitsCount--;
}

void ABaseGameMode::IncreaseSickRabbitsCount()
{
	SickRabbitsCount++;
}

void ABaseGameMode::DecreaseSickRabbitsCount()
{
	SickRabbitsCount--;
}

void ABaseGameMode::RabbitsPayOff()
{
	if (!CollectorCurrentRow || !LivingHole)
	{
		return;
	}

	const TArray<FRabbitParameters>& RabbitsParameters = LivingHole->GetRabbitsParameters();
	int32 CurrentPayoffCount = CollectorCurrentRow->PayoffRabbitsCount;
	TArray<FRabbitParameters> AuxiliaryRabbitsParameters;

	if (RabbitsParameters.Num() > CurrentPayoffCount)
	{
		for (int32 i = 0; i < RabbitsParameters.Num() - CurrentPayoffCount; i++)
		{
			if (RabbitsParameters.IsValidIndex(i))
			{
				AuxiliaryRabbitsParameters.Add(RabbitsParameters[i]);
			}
		}
	}
	else
	{
		AuxiliaryRabbitsParameters.Empty();
	}

	LivingHole->SetRabbitsParameters(AuxiliaryRabbitsParameters);
	LivingHole->TotalRabbitsCount = RabbitsParameters.Num();
}

void ABaseGameMode::RabbitsRefuseToPayOff()
{
	if (!CollectorCurrentRow || !LivingHole)
	{
		return;
	}

	const TArray<FRabbitParameters>& RabbitsParameters = LivingHole->GetRabbitsParameters();
	TArray<FRabbitParameters> AuxiliaryRabbitsParameters;
	RandomNonPayoffRabbitsCount = FMath::RandRange(CollectorCurrentRow->NonPayoffRabbitsCountMin, CollectorCurrentRow->NonPayoffRabbitsCountMax);

	if (RabbitsParameters.Num() > RandomNonPayoffRabbitsCount)
	{
		for (int32 i = 0; i < RabbitsParameters.Num() - RandomNonPayoffRabbitsCount; i++)
		{
			if (RabbitsParameters.IsValidIndex(i))
			{
				AuxiliaryRabbitsParameters.Add(RabbitsParameters[i]);
			}
		}
	}
	else
	{
		AuxiliaryRabbitsParameters.Empty();
		RandomNonPayoffRabbitsCount = RabbitsParameters.Num();
	}
	
	LivingHole->SetRabbitsParameters(AuxiliaryRabbitsParameters);
	LivingHole->TotalRabbitsCount = RabbitsParameters.Num();
}
