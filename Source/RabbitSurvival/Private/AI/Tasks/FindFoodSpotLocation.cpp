// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/FindFoodSpotLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Rabbit/Rabbit.h"
#include "FoodSpot/FoodSpot.h"

UFindFoodSpotLocation::UFindFoodSpotLocation()
{
	NodeName = "FindFoodSpotLocation";
}

EBTNodeResult::Type UFindFoodSpotLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* Controller = OwnerComp.GetAIOwner();
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Controller || !Blackboard) return EBTNodeResult::Failed;

	ARabbit* Rabbit = Cast<ARabbit>(Controller->GetPawn());
	if (!Rabbit) return EBTNodeResult::Failed;

	if(Rabbit->GetRabbitParameters().AssignedFoodSpot->GetCurrentFood() <= 0) return EBTNodeResult::Failed;

	FVector AssignedCollectionSpotLocation = Rabbit->GetRabbitParameters().AssignedCollectionSeat->GetComponentLocation();
	if (AssignedCollectionSpotLocation.IsZero()) return EBTNodeResult::Failed;

	Blackboard->SetValueAsVector(CollectionSpotKey.SelectedKeyName, AssignedCollectionSpotLocation);
	return EBTNodeResult::Succeeded;
}
