// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TakeFrozenRabbit.generated.h"

class ABasePlayerController;
class ARabbit;

UCLASS()
class RABBITSURVIVAL_API UTakeFrozenRabbit : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UTakeFrozenRabbit();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	ABasePlayerController* BasePC;
	ARabbit* FrozenRabbit;
};
