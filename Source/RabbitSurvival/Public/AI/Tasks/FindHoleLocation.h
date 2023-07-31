// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Hole/LivingHole.h"
#include "FindHoleLocation.generated.h"

UCLASS()
class RABBITSURVIVAL_API UFindHoleLocation : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UFindHoleLocation();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBlackboardKeySelector LocationKey;

	TSubclassOf<ALivingHole> HoleClass = ALivingHole::StaticClass();
};
