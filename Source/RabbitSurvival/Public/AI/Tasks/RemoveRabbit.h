// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Hole/LivingHole.h"
#include "RemoveRabbit.generated.h"

UCLASS()
class RABBITSURVIVAL_API URemoveRabbit : public UBTTaskNode
{
	GENERATED_BODY()

public:
	URemoveRabbit();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	TSubclassOf<ALivingHole> LivingHoleClass = ALivingHole::StaticClass();
};
