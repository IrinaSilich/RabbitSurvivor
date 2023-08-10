// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Tasks/FindFrozenRabbitLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Rabbit/Rabbit.h"

UFindFrozenRabbitLocation::UFindFrozenRabbitLocation()
{
	NodeName = "FindFrozenRabbitLocation";
}

EBTNodeResult::Type UFindFrozenRabbitLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard) return EBTNodeResult::Failed;

	FrozenRabbit = Cast<ARabbit>(Blackboard->GetValueAsObject(RabbitToRescue.SelectedKeyName));
	if (!FrozenRabbit) return EBTNodeResult::Failed;

	FVector FrozenRabbitLocation = FrozenRabbit->GetActorLocation();
	if (FrozenRabbitLocation.IsZero()) return EBTNodeResult::Failed;

	FRabbitParameters FrozenRabbitParameters = FrozenRabbit->GetRabbitParameters();
	FrozenRabbitParameters.IsPendingRescue = true;
	FrozenRabbit->SetRabbitParameters(FrozenRabbitParameters);

	Blackboard->SetValueAsVector(LocationKey.SelectedKeyName, FrozenRabbitLocation);
	return EBTNodeResult::Succeeded;
}