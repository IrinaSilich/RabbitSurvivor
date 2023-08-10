// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/SetRabbitToRescue.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PlayerController/BasePlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Rabbit/Rabbit.h"

USetRabbitToRescue::USetRabbitToRescue()
{
	NodeName = "SetRabbitToRescue";
}

EBTNodeResult::Type USetRabbitToRescue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard) return EBTNodeResult::Failed;

	BasePC = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!BasePC) return EBTNodeResult::Failed;

	FrozenRabbit = BasePC->GetFrozenRabbit();
	if (!FrozenRabbit) return EBTNodeResult::Failed;

	Blackboard->SetValueAsObject(RabbitToRescue.SelectedKeyName, FrozenRabbit);
	return EBTNodeResult::Succeeded;
}