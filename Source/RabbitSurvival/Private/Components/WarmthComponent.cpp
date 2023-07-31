// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/WarmthComponent.h"

UWarmthComponent::UWarmthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UWarmthComponent::BeginPlay()
{
	Super::BeginPlay();

	WarmthOwner = Cast<ARabbit>(GetOwner());

	GetWorld()->GetTimerManager().SetTimer(WarmthDecreaseTimer, this, &UWarmthComponent::WarmthDecrease, WarmthDecreaseSpeed, true);
}

void UWarmthComponent::WarmthDecrease()
{
	FRabbitParameters FreezingRabbitParameters = WarmthOwner->GetRabbitParameters();
	FreezingRabbitParameters.WarmthStamina = FMath::Clamp(WarmthOwner->GetRabbitParameters().WarmthStamina - WarmthDecreaseAmount * WarmthOwner->WarmthDecreaseCurrentRate, 0.f, 100.f);
	WarmthOwner->SetRabbitParameters(FreezingRabbitParameters);

	if (WarmthOwner->GetRabbitParameters().WarmthStamina <= 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(WarmthDecreaseTimer);

		FRabbitParameters FreezedRabbitParameters = WarmthOwner->GetRabbitParameters();
		FRabbitResourceCollection FreezedRabbitResources = WarmthOwner->GetRabbitResources();

		FreezedRabbitParameters.IsFrozen = true;
		FreezedRabbitParameters.IsTaskProcessed = false;
		FreezedRabbitParameters.TaskAssigned = RabbitActivity::None;
		WarmthOwner->SetRabbitParameters(FreezedRabbitParameters);

		FreezedRabbitResources.CurrentAmount = FMath::Floor(WarmthOwner->GetRabbitResources().CurrentAmount / 2.f);
		WarmthOwner->SetRabbitResources(FreezedRabbitResources);

		WarmthOwner->RabbitIsFrozen();

		GetWorld()->GetTimerManager().SetTimer(GetSickTimer, this, &UWarmthComponent::RabbitGotSick, TimeBeforeRabbitGetSick, false);
	}
}

void UWarmthComponent::RabbitGotSick()
{
	FRabbitParameters SickRabbitParameters = WarmthOwner->GetRabbitParameters();

	SickRabbitParameters.IsSick = true;
	WarmthOwner->SetRabbitParameters(SickRabbitParameters);

	WarmthOwner->RabbitIsSick();
}