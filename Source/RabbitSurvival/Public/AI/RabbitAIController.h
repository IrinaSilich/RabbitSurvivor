// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RabbitAIController.generated.h"

UCLASS()
class RABBITSURVIVAL_API ARabbitAIController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Behaviour Tree")
	UBehaviorTree* BTRabbit;
};
