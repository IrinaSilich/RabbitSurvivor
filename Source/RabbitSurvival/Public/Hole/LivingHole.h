// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Hole/BaseHole.h"
#include "LivingHole.generated.h"

UCLASS()
class RABBITSURVIVAL_API ALivingHole : public ABaseHole
{
	GENERATED_BODY()

public:
	ALivingHole();

	UFUNCTION(BlueprintCallable)
	virtual void InitHole() override;

	UFUNCTION(BlueprintCallable)
	virtual void CheckForFrozenRabbitsInGeneralSection() override;

	UFUNCTION(BlueprintCallable)
	virtual void SetRabbitsParameters(TArray<FRabbitParameters> RabbitsParametersToSet) override { RabbitsParameters = RabbitsParametersToSet; };

	UFUNCTION(BlueprintCallable)
	virtual void SetWarmingUpRabbitsParameters(TArray<FRabbitParameters> WarmingUpRabbitsParametersToSet) override { WarmedUpRabbitsParameters = WarmingUpRabbitsParametersToSet; };

	UFUNCTION(BlueprintCallable)
	virtual const TArray<FRabbitParameters>& GetRabbitsParameters() const override { return RabbitsParameters; };

	UFUNCTION(BlueprintCallable)
	virtual const TArray<FRabbitParameters>& GetWarmedUpRabbitsParameters() const override { return WarmedUpRabbitsParameters; };

	UFUNCTION(BlueprintCallable)
	virtual const TArray<FRabbitParameters>& GetBreedingRabbitsParameters() const override { return BreedRabbitsParameters; };

	UFUNCTION(BlueprintCallable)
	virtual const TArray<FRabbitParameters>& GetHospitalizedRabbitsParameters() const override { return HospitalizedRabbitsParameters; };

	UFUNCTION(BlueprintCallable)
	virtual const TArray<FRabbitParameters>& GetTreatedRabbitsParameters() const override { return TreatedRabbitsParameters; };

	UFUNCTION(BlueprintCallable)
	virtual TArray<ARabbit*> GetRabbitsOutsideHole() const override { return RabbitsOutsideHole; };

	UFUNCTION(BlueprintCallable)
	virtual ARabbit* SpawnRabbit(RabbitActivity AssignedTask, AFoodSpot* AssignedFoodSpot, USceneComponent* AssignedCollectionSpot) override;

	UFUNCTION(BlueprintCallable)
	virtual void RemoveRabbit(ARabbit* RabbitToRemove) override;

	UFUNCTION(BlueprintCallable)
	virtual void CheckForFoodAndPairRabbitsToBreed() override;

	UFUNCTION(BlueprintCallable)
	virtual void SetUpHealing() override;

	virtual void TellGameModeRabbitIsFrozen() override;

	virtual void TellGameModeRabbitIsSick() override;

	UFUNCTION(BlueprintCallable)
	bool IfEnoughFoodForOneBreed() const;

	UFUNCTION(BlueprintCallable)
	bool IfEnoughFoodForOneHeal() const;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnLivingHoleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UFUNCTION()
	virtual void WarmingUpRabbits() override;

	UFUNCTION()
	virtual void HealingRabbits() override;

	virtual void BreedNewRabbit() override;

	virtual void NewRabbitsBorn() override;

	UPROPERTY(EditDefaultsOnly, Category = "Const Properties")
	UDataTable* GameConstProperties;

	FGameConstProperties* PropertiesRow;

	TArray<FName> PropertiesRowNames;
};
