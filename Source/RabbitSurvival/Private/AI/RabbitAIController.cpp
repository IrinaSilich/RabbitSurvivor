// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/RabbitAIController.h"

void ARabbitAIController::BeginPlay()
{
	Super::BeginPlay();

	if (BTRabbit)
	{
		RunBehaviorTree(BTRabbit);
	}
}
