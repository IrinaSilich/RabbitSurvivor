// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "FindFoodSpotLocation.generated.h"

UCLASS()
class RABBITSURVIVAL_API UFindFoodSpotLocation : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UFindFoodSpotLocation();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBlackboardKeySelector CollectionSpotKey;
};
