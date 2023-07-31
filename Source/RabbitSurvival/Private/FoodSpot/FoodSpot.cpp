// Fill out your copyright notice in the Description page of Project Settings.

#include "FoodSpot/FoodSpot.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Rabbit/Rabbit.h"

AFoodSpot::AFoodSpot()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("Scene Component");
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh Component");
	SphereCollision = CreateDefaultSubobject<USphereComponent>("Sphere Collision");

	SetRootComponent(SceneComponent);
	MeshComponent->SetupAttachment(SceneComponent);
	SphereCollision->SetupAttachment(SceneComponent);

	FString SeatName = "Collection Spot ";

	for (int i = 0; i < MaxRabbitsAssignedToBush; i++)
	{
		FName CollectionSpotComponentName = FName(SeatName + FString::FromInt(i + 1));
		CollectionSeats.Add(CreateDefaultSubobject<USceneComponent>(CollectionSpotComponentName));
		CollectionSeats[i]->SetupAttachment(MeshComponent);
	}
}

void AFoodSpot::BeginPlay()
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

void AFoodSpot::SetCurrentFood(float NewFoodAmount)
{
	CurrentFood = NewFoodAmount;
	
	if (CurrentFood <= 0)
	{
		RespawnFoodAndActivateCollectionSeats();
	}
		
	ChangeBareBushMesh();
}

USceneComponent* AFoodSpot::ChooseCollectionSeat()
{
	if (CollectionSeats.IsEmpty())
	{
		return nullptr;
	}

	int32 i = 0;

	for (i = 0; i < CollectionSeats.Num(); i++)
	{
		if (CollectionSeats[i]->IsActive())
		{
			CollectionSeats[i]->Deactivate();
		}
		else
		{
			continue;
		}

		break;
	}

	return CollectionSeats[i];
}

void AFoodSpot::RespawnFoodAndActivateCollectionSeats()
{
	if (!PropertiesRow)
	{
		return;
	}

	AssignedRabbits.Empty();

	FTimerHandle RespawnFoodTimer;
	FTimerHandle ActivateCollectionSeatsTimer;
	GetWorldTimerManager().SetTimer(RespawnFoodTimer, this, &AFoodSpot::IncreaseCurrentFood, PropertiesRow->FoodRespawnTime, false);
	GetWorldTimerManager().SetTimer(ActivateCollectionSeatsTimer, this, &AFoodSpot::ActivateAllCollectionSeatsBack, PropertiesRow->FoodRespawnTime, false);
}

void AFoodSpot::IncreaseCurrentFood()
{
	if (!PropertiesRow)
	{
		return;
	}

	SetCurrentFood(FMath::RandRange(PropertiesRow->MinFoodOnBush, PropertiesRow->MaxFoodOnBush));
}

void AFoodSpot::ActivateAllCollectionSeatsBack()
{
	if (CollectionSeats.IsEmpty())
	{
		return;
	}

	for (int32 i = 0; i < CollectionSeats.Num(); i++)
	{
		CollectionSeats[i]->Activate();
	}
}

void AFoodSpot::ActivateSeatWhenFoodCollectionCancelled(USceneComponent* CollectionSeatToFreeUp)
{
	if (!CollectionSeatToFreeUp)
	{
		return;
	}

	int32 CollectionSeatToFreeUpIndex = CollectionSeats.Find(CollectionSeatToFreeUp);

	if (!CollectionSeats[CollectionSeatToFreeUpIndex]->IsActive())
	{
		CollectionSeats[CollectionSeatToFreeUpIndex]->Activate();
	}
}

void AFoodSpot::ChangeBareBushMesh()
{
	UStaticMeshComponent* StaticMeshComponent = FindComponentByClass<UStaticMeshComponent>();

	if (!StaticMeshComponent)
	{
		return;
	}

	if (CurrentFood > 0 && StaticMeshComponent->GetStaticMesh() != FullBushMesh)
	{
		StaticMeshComponent->SetStaticMesh(FullBushMesh);
	}
	else if (CurrentFood <= 0 && StaticMeshComponent->GetStaticMesh() != BareBushMesh)
	{
		StaticMeshComponent->SetStaticMesh(BareBushMesh);
	}	
}

void AFoodSpot::SetRabbitFreezingRate()
{
	if (AssignedRabbits.IsEmpty())
	{
		return;
	}

	switch (AssignedRabbits.Num())
	{
	case 1:
		for (int j = 0; j < AssignedRabbits.Num(); j++)
		{
			if (AssignedRabbits[j])
			{
				AssignedRabbits[j]->WarmthDecreaseCurrentRate = AssignedRabbits[j]->WarmthDecreaseRates.ForOneRabbitByBush;
			}
		}
		break;
	case 2:
		for (int j = 0; j < AssignedRabbits.Num(); j++)
		{
			if (AssignedRabbits[j])
			{
				AssignedRabbits[j]->WarmthDecreaseCurrentRate = AssignedRabbits[j]->WarmthDecreaseRates.ForTwoRabbitsByBush;
			}
		}
		break;
	case 3:
		for (int j = 0; j < AssignedRabbits.Num(); j++)
		{
			if (AssignedRabbits[j])
			{
				AssignedRabbits[j]->WarmthDecreaseCurrentRate = AssignedRabbits[j]->WarmthDecreaseRates.ForThreeRabbitsByBush;
			}
		}
		break;
	case 4:
		for (int j = 0; j < AssignedRabbits.Num(); j++)
		{
			if (AssignedRabbits[j])
			{
				AssignedRabbits[j]->WarmthDecreaseCurrentRate = AssignedRabbits[j]->WarmthDecreaseRates.ForFourRabbitsByBush;
			}
		}
		break;
	default:
		for (int j = 0; j < AssignedRabbits.Num(); j++)
		{
			if (AssignedRabbits[j])
			{
				AssignedRabbits[j]->WarmthDecreaseCurrentRate = AssignedRabbits[j]->WarmthDecreaseRates.ForFourRabbitsByBush;
			}
		}
		break;
	}
}

void AFoodSpot::IncreaseRabbitsAssigned(ARabbit* NewRabbitAssigned)
{ 
	if (NewRabbitAssigned)
	{
		AssignedRabbits.Add(NewRabbitAssigned);
	}
}

void AFoodSpot::DecreaseRabbitsAssigned(ARabbit* RabbitToSentBack)
{ 
	if (RabbitToSentBack)
	{
		AssignedRabbits.Remove(RabbitToSentBack);
	}
}