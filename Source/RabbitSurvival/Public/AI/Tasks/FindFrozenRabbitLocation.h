// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "FindFrozenRabbitLocation.generated.h"

class ABasePlayerController;

UCLASS()
class RABBITSURVIVAL_API UFindFrozenRabbitLocation : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UFindFrozenRabbitLocation();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBlackboardKeySelector LocationKey;

	ABasePlayerController* BasePC;
};
