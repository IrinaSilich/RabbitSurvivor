// Fill out your copyright notice in the Description page of Project Settings.


// Fill out your copyright notice in the Description page of Project Settings.


//#include "AI/Tasks/CollectFood.h"
//
//UCollectFood::UCollectFood()
//{
//	NodeName = "CollectFood";
//}
//
//EBTNodeResult::Type UCollectFood::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
//{
//	AAIController* Controller = OwnerComp.GetAIOwner();
//	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
//	if(!Controller || !Blackboard)
//	{
//		return EBTNodeResult::Failed;
//	}
//
//	ARabbit* Rabbit = Cast<ARabbit>(Controller->GetPawn());
//	if(!Rabbit)
//	{
//		return EBTNodeResult::Failed;
//	}
//
//	if(Rabbit->GetRabbitResources().TimeForCollecting < 0)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("Time for collecting is bad"));
//		return EBTNodeResult::Failed;
//	}
//
//	if(Rabbit->GetRabbitParameters().AssignedFoodSpot->GetCurrentFoodOnSpot() < 0)
//	{
//		return EBTNodeResult::Failed;
//	}
//
//	FRabbitParameters rabbitParameters = Rabbit->GetRabbitParameters();
//	rabbitParameters.IsTaskProcessed = true;
//	Rabbit->SetRabbitParameters(rabbitParameters);
//
//	EBTNodeResult::Type a;
//	FTimerHandle TimerHandle;
//	OwnerComp.GetWorld()->GetTimerManager().SetTimer(TimerHandle, [Rabbit, &TimerHandle, &a]()
//		{
//			FTimerManager TimerManager;
//			FRabbitParameters rabbitParameters = Rabbit->GetRabbitParameters();
//			FRabbitResourceCollection rabbitResources = Rabbit->GetRabbitResources();
//
//			if(Rabbit->GetRabbitResources().CurrentAmount == Rabbit->GetRabbitResources().MaxAmount ||
//				Rabbit->GetRabbitParameters().AssignedFoodSpot->GetCurrentFoodOnSpot() <= 0)
//			{
//				TimerManager.ClearTimer(TimerHandle);
//				rabbitParameters.IsTaskProcessed = false;
//				if(Rabbit->GetRabbitParameters().AssignedFoodSpot->GetCurrentFoodOnSpot() <= 0)
//				{
//					rabbitParameters.TaskAssigned = RabbitActivity::None;
//				}
//				Rabbit->SetRabbitParameters(rabbitParameters);
//				a = EBTNodeResult::Succeeded;
//				return;
//			}
//
//			if(Rabbit->GetRabbitParameters().AssignedFoodSpot->GetCurrentFoodOnSpot() > 0)
//			{
//				Rabbit->GetRabbitParameters().AssignedFoodSpot->SetCurrentFoodOnSpot(
//					Rabbit->GetRabbitParameters().AssignedFoodSpot->GetCurrentFoodOnSpot() - 1);
//				UE_LOG(LogTemp, Error, TEXT("--------Food: %i"), Rabbit->GetRabbitParameters().AssignedFoodSpot->GetCurrentFoodOnSpot());
//
//				rabbitResources.CurrentAmount = rabbitResources.CurrentAmount + 1;
//				Rabbit->SetRabbitResources(rabbitResources);
//			}
//
//			a = EBTNodeResult::InProgress;
//			return;
//		}, 2.0f, true);
//	return a;
//}