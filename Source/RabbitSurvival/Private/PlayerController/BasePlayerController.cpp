// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerController/BasePlayerController.h"
#include "Kismet/GameplayStatics.h"

void ABasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetPlayerView();
}

void ABasePlayerController::SetPlayerView()
{
	AActor* PlayerView = UGameplayStatics::GetActorOfClass(GetWorld(), CameraView);

	if (PlayerView)
	{
		SetViewTarget(PlayerView);
	}
}
