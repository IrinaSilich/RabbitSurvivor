// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "SetRabbitToRescue.generated.h"

class ABasePlayerController;
class ARabbit;

UCLASS()
class RABBITSURVIVAL_API USetRabbitToRescue : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	USetRabbitToRescue();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBlackboardKeySelector RabbitToRescue;

	ABasePlayerController* BasePC;
	ARabbit* FrozenRabbit;
};
