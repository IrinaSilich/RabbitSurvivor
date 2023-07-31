// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/TakeFrozenRabbit.h"
#include "FoodSpot/FoodSpot.h"
#include "PlayerController/BasePlayerController.h"
#include "Rabbit/Rabbit.h"
#include "Kismet/GameplayStatics.h"

UTakeFrozenRabbit::UTakeFrozenRabbit()
{
	NodeName = "TakeFrozenRabbit";
}

EBTNodeResult::Type UTakeFrozenRabbit::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	BasePC = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!BasePC) return EBTNodeResult::Failed;

	FrozenRabbit = BasePC->GetFrozenRabbit();
	if (!FrozenRabbit) return EBTNodeResult::Failed;
	 
	FRabbitParameters FrozenRabbitParameters = FrozenRabbit->GetRabbitParameters();
	FrozenRabbitParameters.AssignedFoodSpot->ActivateSeatWhenFoodCollectionCancelled(FrozenRabbitParameters.AssignedCollectionSeat);
	FrozenRabbitParameters.AssignedFoodSpot->DecreaseRabbitsAssigned(FrozenRabbit);
	FrozenRabbitParameters.AssignedFoodSpot = nullptr;
	FrozenRabbitParameters.AssignedCollectionSeat = nullptr;

	if (FrozenRabbitParameters.IsFrozen == true && FrozenRabbitParameters.IsSick == false)
	{
		FrozenRabbitParameters.TaskAssigned = RabbitActivity::WarmUp;
		FrozenRabbitParameters.IsFrozen = false;
		FrozenRabbit->SetRabbitParameters(FrozenRabbitParameters);
	}
	else if (FrozenRabbitParameters.IsFrozen == true && FrozenRabbitParameters.IsSick == true)
	{
		FrozenRabbitParameters.TaskAssigned = RabbitActivity::Treated;
		FrozenRabbitParameters.IsFrozen = false;
		FrozenRabbitParameters.IsSick = false;
		FrozenRabbit->SetRabbitParameters(FrozenRabbitParameters);
	}
	
	return EBTNodeResult::Succeeded;
}