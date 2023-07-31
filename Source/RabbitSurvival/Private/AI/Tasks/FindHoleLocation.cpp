// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/FindHoleLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UFindHoleLocation::UFindHoleLocation()
{
	NodeName = "FindHoleLocation";
}

EBTNodeResult::Type UFindHoleLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard) return EBTNodeResult::Failed;

	ALivingHole* Hole = Cast<ALivingHole>(UGameplayStatics::GetActorOfClass(GetWorld(), HoleClass));
	if (!Hole) return EBTNodeResult::Failed;

	FVector HoleLocation = Hole->GetActorLocation();

	Blackboard->SetValueAsVector(LocationKey.SelectedKeyName, HoleLocation);
	return EBTNodeResult::Succeeded;
}
