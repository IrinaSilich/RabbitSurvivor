// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/FindFrozenRabbitLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PlayerController/BasePlayerController.h"
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

	BasePC = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!BasePC) return EBTNodeResult::Failed;

	FVector FrozenRabbitLocation = BasePC->GetFrozenRabbit()->GetActorLocation();
	if (FrozenRabbitLocation.IsZero()) return EBTNodeResult::Failed;

	Blackboard->SetValueAsVector(LocationKey.SelectedKeyName, FrozenRabbitLocation);
	return EBTNodeResult::Succeeded;
}