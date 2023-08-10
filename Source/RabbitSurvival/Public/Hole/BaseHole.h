// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Rabbit/Rabbit.h"
#include "BaseHole.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRabbitsCountChanged);
DECLARE_MULTICAST_DELEGATE(FOnIncreaseFrozenRabbitsCount);
DECLARE_MULTICAST_DELEGATE(FOnDecreaseFrozenRabbitsCount);
DECLARE_MULTICAST_DELEGATE(FOnIncreaseSickRabbitsCount);
DECLARE_MULTICAST_DELEGATE(FOnDecreaseSickRabbitsCount);

class UBoxComponent;

UCLASS()
class RABBITSURVIVAL_API ABaseHole : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseHole();

	UPROPERTY(BlueprintAssignable)
	FOnRabbitsCountChanged OnRabbitsCountChanged;

	FOnIncreaseFrozenRabbitsCount OnIncreaseFrozenRabbitsCount;

	FOnDecreaseFrozenRabbitsCount OnDecreaseFrozenRabbitsCount;

	FOnIncreaseSickRabbitsCount OnIncreaseSickRabbitsCount;

	FOnDecreaseSickRabbitsCount OnDecreaseSickRabbitsCount;

	virtual void SetRabbitsParameters(TArray<FRabbitParameters> RabbitsParametersToSet) { RabbitsParameters = RabbitsParametersToSet; };

	virtual void SetWarmingUpRabbitsParameters(TArray<FRabbitParameters> WarmingUpRabbitsParametersToSet) { WarmedUpRabbitsParameters = WarmingUpRabbitsParametersToSet; };

	virtual const TArray<FRabbitParameters>& GetRabbitsParameters() const { return RabbitsParameters; };

	virtual const TArray<FRabbitParameters>& GetWarmedUpRabbitsParameters() const { return WarmedUpRabbitsParameters; };

	virtual const TArray<FRabbitParameters>& GetHospitalizedRabbitsParameters() const { return HospitalizedRabbitsParameters; };

	virtual const TArray<FRabbitParameters>& GetTreatedRabbitsParameters() const { return TreatedRabbitsParameters; };

	virtual const TArray<FRabbitParameters>& GetBreedingRabbitsParameters() const { return BreedRabbitsParameters; };

	virtual TArray<ARabbit*> GetRabbitsOutsideHole() const { return RabbitsOutsideHole; };

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Rabbits Count")
	int32 TotalRabbitsCount {0};

protected:
	virtual void BeginPlay() override;

	virtual void InitHole();

	virtual void CheckForFrozenRabbitsInGeneralSection();

	virtual ARabbit* SpawnRabbit(RabbitActivity AssignedTask, AFoodSpot* AssignedFoodSpot, USceneComponent* AssignedCollectionSpot);

	virtual void RemoveRabbit(ARabbit* RabbitToRemove);

	virtual void CheckForFoodAndPairRabbitsToBreed();

	virtual void BreedNewRabbit(); 
	
	virtual void NewRabbitsBorn();

	virtual void WarmingUpRabbits();

	virtual void SetUpHealing();

	virtual void HealingRabbits();

	virtual void TellGameModeRabbitIsFrozen();

	UFUNCTION()
	virtual void TellGameModeRabbitIsSick();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USceneComponent* SceneComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UBoxComponent* BoxCollision;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Breed")
	FTimerHandle BreedRabbitTimer;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Freeze")
	FTimerHandle WarmUpTimer;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Freeze")
	FTimerHandle HealTimer;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Freeze")
	FTimerHandle HealCheckTimer;

	UPROPERTY(VisibleDefaultsOnly, Category = "General Rabbit Data")
	FRabbitParameters StartParameters = { RabbitClass::General, RabbitActivity::None, 100.f, false, false, false, false, nullptr, nullptr };

	UPROPERTY(VisibleDefaultsOnly, Category = "General Rabbit Data")
	FRabbitParameters AssignedParameters;

	UPROPERTY(VisibleDefaultsOnly, Category = "General Rabbit Data")
	TArray<FRabbitParameters> RabbitsParameters;

	UPROPERTY(VisibleDefaultsOnly, Category = "General Rabbit Data")
	TArray<ARabbit*> RabbitsOutsideHole;

	UPROPERTY(VisibleDefaultsOnly, Category = "Breed")
	TArray<FRabbitParameters> BreedRabbitsParameters;

	UPROPERTY(VisibleDefaultsOnly, Category = "Freeze")
	TArray<FRabbitParameters> WarmedUpRabbitsParameters;

	UPROPERTY(VisibleDefaultsOnly, Category = "Freeze")
	TArray<FRabbitParameters> HospitalizedRabbitsParameters;

	UPROPERTY(VisibleDefaultsOnly, Category = "Freeze")
	TArray<FRabbitParameters> TreatedRabbitsParameters;

	UPROPERTY(EditDefaultsOnly, Category = "Freeze", meta = (ClampMin = "0.0", ClampMax = "100.0"))
	float WarmUpTimerInterval {1.f};

	UPROPERTY(EditDefaultsOnly, Category = "Freeze", meta = (ClampMin = "0.0", ClampMax = "100.0"))
	float WarmUpAmountPerInterval {1.f};

	UPROPERTY(EditDefaultsOnly, Category = "Freeze", meta = (ClampMin = "0.0", ClampMax = "100.0"))
	float HealTimerInterval {1.f};

	UPROPERTY(EditDefaultsOnly, Category = "Freeze", meta = (ClampMin = "0.0", ClampMax = "100.0"))
	float HealAmountPerInterval {1.f};

	UPROPERTY(EditDefaultsOnly, Category = "Freeze", meta = (ClampMin = "0.0", ClampMax = "100.0"))
	float HealCheckTimerInterval {1.f};

	UPROPERTY(EditDefaultsOnly, Category = "Freeze", meta = (ClampMin = "0.0", ClapmMax = "100.0"))
	float HoleWarmUpCoefficient {1.f};

	UPROPERTY(EditDefaultsOnly, Category = "Freeze", meta = (ClampMin = "0.0", ClapmMax = "100.0"))
	float BreedRoomWarmUpCoefficient {0.5f};

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	TSubclassOf<ARabbit> RabbitClass = ARabbit::StaticClass();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Food")
	float FoodAmountCollected;

	ARabbit* SpawnedRabbit;
};
