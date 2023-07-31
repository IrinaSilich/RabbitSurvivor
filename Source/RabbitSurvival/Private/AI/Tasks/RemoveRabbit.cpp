// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/RemoveRabbit.h"
#include "AIController.h"
#include "Rabbit/Rabbit.h"
#include "Kismet/GameplayStatics.h"

URemoveRabbit::URemoveRabbit()
{
	NodeName = "Remove Rabbit";
}

EBTNodeResult::Type URemoveRabbit::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* Controller = OwnerComp.GetAIOwner();
	if (!Controller) return EBTNodeResult::Failed;

	ARabbit* Rabbit = Cast<ARabbit>(Controller->GetPawn());
	if (!Rabbit) return EBTNodeResult::Failed;

	ALivingHole* LivingHole = Cast<ALivingHole>(UGameplayStatics::GetActorOfClass(GetWorld(), LivingHoleClass));
	if (!LivingHole) return EBTNodeResult::Failed;

	LivingHole->RemoveRabbit(Rabbit);

	return EBTNodeResult::Succeeded;
}

