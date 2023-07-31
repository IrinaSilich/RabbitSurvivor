// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Engine/DataTable.h"
#include "Hole/LivingHole.h"
#include "BaseGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCollectorRowIndexChanged, int32, CollectorRowIndex);

UENUM(BlueprintType)
enum class RabbitsCollectorType : uint8
{
	Farmer,
	Fox,
	Wolf,
	Bear
};

USTRUCT(BlueprintType)
struct FRabbitsCollectorEventsData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float TimeBeforeEventHappens;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	RabbitsCollectorType RabbitsCollector;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 PayoffRabbitsCount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 NonPayoffRabbitsCountMin;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 NonPayoffRabbitsCountMax;
};

USTRUCT(BlueprintType)
struct FTasksData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool IsAlwaysAvailable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 UnlockTaskID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Duration;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Description;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Reward;
};

UCLASS()
class RABBITSURVIVAL_API ABaseGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABaseGameMode();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver();

	UFUNCTION(BlueprintImplementableEvent)
	void RabbitsAreTaken(int32 CollectorRowIndex);

	void IncreaseFrozenRabbitsCount();

	void DecreaseFrozenRabbitsCount();

	void IncreaseSickRabbitsCount();

	void DecreaseSickRabbitsCount();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Rabbits Count")
	int32 FrozenRabbitsCount {0};

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Rabbits Count")
	int32 SickRabbitsCount {0};

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void RabbitsPayOff();

	UFUNCTION(BlueprintCallable)
	void RabbitsRefuseToPayOff();

	UFUNCTION(BlueprintCallable)
	void GetCollectorGurrentRow(int32 CollectorRowIndex);

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Meta")
	FTimerHandle CollectionTimer;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Meta")
	int32 CollectorCurrentRowIndex {0};

	UPROPERTY(BlueprintAssignable)
	FOnCollectorRowIndexChanged OnCollectorRowIndexChanged;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Meta")
	int32 RandomNonPayoffRabbitsCount {0};

private:
	UFUNCTION()
	void SomeoneHasComeForRabbits();

	UPROPERTY(VisibleDefaultsOnly, Category = "Meta")
	UDataTable* RabbitsCollectorEventsData;

	UPROPERTY(VisibleDefaultsOnly, Category = "Meta")
	UDataTable* TasksData;

	TArray<FName> CollectorRowNames;

	FRabbitsCollectorEventsData* CollectorCurrentRow;

	ALivingHole* LivingHole;

	TSubclassOf<ALivingHole> LivingHoleClass = ALivingHole::StaticClass();
};
