// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Auxiliaries/RabbitUtilities.h"
#include "Engine/DataTable.h"
#include "FoodSpot.generated.h"

class ARabbit;
class USphereComponent;

UCLASS()
class RABBITSURVIVAL_API AFoodSpot : public AActor
{
	GENERATED_BODY()

public:
	AFoodSpot();

	UFUNCTION(BlueprintCallable)
	float GetCurrentFood() const { return CurrentFood; };

	UFUNCTION(BlueprintCallable)
	void SetCurrentFood(float NewFoodAmount);

	UFUNCTION(BlueprintCallable)
	TArray<ARabbit*> GetRabbitsAssigned() const { return AssignedRabbits; };

	UFUNCTION(BlueprintCallable)
	void IncreaseRabbitsAssigned(ARabbit* NewRabbitAssigned);

	UFUNCTION(BlueprintCallable)
	void DecreaseRabbitsAssigned(ARabbit* RabbitToSentBack);

	UFUNCTION(BlueprintCallable)
	void SetRabbitFreezingRate();

	void ActivateSeatWhenFoodCollectionCancelled(USceneComponent* CollectionSeatToFreeUp);

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	USceneComponent* ChooseCollectionSeat();

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* SceneComponent;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly)
	USphereComponent* SphereCollision;

	UPROPERTY(VisibleAnywhere)
	TArray<USceneComponent*> CollectionSeats;

	UPROPERTY(EditDefaultsOnly, Category = "Visuals")
	UStaticMesh* BareBushMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Visuals")
	UStaticMesh* FullBushMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "1", ClampMax = "4"))
	int32 MaxRabbitsAssignedToBush {4};

private:
	void RespawnFoodAndActivateCollectionSeats();

	void IncreaseCurrentFood();

	void ActivateAllCollectionSeatsBack();

	void ChangeBareBushMesh();

	UPROPERTY(VisibleAnywhere, Category = "Food")
	float CurrentFood {0.f};

	UPROPERTY(VisibleAnywhere, Category = "Rabbit Data")
	TArray<ARabbit*> AssignedRabbits;

	UPROPERTY(EditDefaultsOnly, Category = "Const Properties")
	UDataTable* GameConstProperties;

	FGameConstProperties* PropertiesRow;

	TArray<FName> PropertiesRowNames;
};
