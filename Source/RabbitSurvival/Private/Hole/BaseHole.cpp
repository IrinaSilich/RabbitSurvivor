// Fill out your copyright notice in the Description page of Project Settings.

#include "Hole/BaseHole.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

ABaseHole::ABaseHole()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("Scene Component");
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh Component");
	BoxCollision = CreateDefaultSubobject<UBoxComponent>("Box Collision");

	SetRootComponent(SceneComponent);
	MeshComponent->SetupAttachment(SceneComponent);
	BoxCollision->SetupAttachment(SceneComponent);
}

void ABaseHole::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseHole::InitHole()
{

}

void ABaseHole::CheckForFrozenRabbitsInGeneralSection()
{

}

ARabbit* ABaseHole::SpawnRabbit(RabbitActivity AssignedTask, AFoodSpot* AssignedFoodSpot, USceneComponent* AssignedCollectionSpot)
{
	return SpawnedRabbit;
}

void ABaseHole::RemoveRabbit(ARabbit* RabbitToRemove)
{

}

void ABaseHole::CheckForFoodAndPairRabbitsToBreed()
{
	
}

void ABaseHole::BreedNewRabbit()
{

}

void ABaseHole::NewRabbitsBorn()
{

}

void ABaseHole::WarmingUpRabbits()
{

}

void ABaseHole::SetUpHealing()
{

}

void ABaseHole::HealingRabbits()
{

}

void ABaseHole::TellGameModeRabbitIsFrozen()
{

}

void ABaseHole::TellGameModeRabbitIsSick()
{

}
