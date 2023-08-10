#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Engine/DataTable.h"
#include "RabbitUtilities.generated.h"

UENUM(BlueprintType)
enum class RabbitClass : uint8
{
	General,
	Collector,
	Defender,
	Healer,
	Explorer
};

UENUM(BlueprintType)
enum class RabbitActivity : uint8
{
	None,
	CollectFood,
	Breed,
	Rescue,
	WarmUp,
	Treated
};

class AFoodSpot;
class USceneComponent;

USTRUCT(BlueprintType)
struct FRabbitParameters
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	RabbitClass CurrentClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	RabbitActivity TaskAssigned;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float WarmthStamina;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool IsTaskProcessed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool IsFrozen;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool IsSick;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool IsPendingRescue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	AFoodSpot* AssignedFoodSpot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USceneComponent* AssignedCollectionSeat;
};

USTRUCT(BlueprintType)
struct FRabbitResourceCollection
{
	GENERATED_USTRUCT_BODY()

	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	//RabbitClass CurrentClass;
	//тип ресурса

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float CurrentAmount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float IncreaseAmount {0.5f};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float MaxAmount {4.f};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float TimeForCollecting {2.f};
};

USTRUCT(BlueprintType)
struct FGameConstProperties : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "2", ClampMax = "50"))
	int32 RabbitsCountOnStart {10};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "2", ClampMax = "20"))
	int32 MaxRabbitsOnLevel {15};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "2.0", ClampMax = "20.0"))
	float FoodAmountForOneBreed {10.f};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "2.0", ClampMax = "20.0"))
	float FoodAmountForOneHeal {10.f};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "2.0", ClampMax = "20.0"))
	float TimeBeforeRabbitBorn {10.f};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "1", ClampMax = "5"))
	int32 MinNewBornRabbitsCount {1};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "1", ClampMax = "5"))
	int32 MaxNewBornRabbitsCount {3};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "1.0", ClampMax = "4.0"))
	float MinAmountFoodCollectedNotToFreeze {3.f};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "5.0"))
	float TimeBeforeSentToHoleRabbitFreezes {2.f};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "1.0", ClampMax = "128.0"))
	float MaxFoodOnBush {16.f};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "1.0", ClampMax = "128.0"))
	float MinFoodOnBush {4.f};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "5.0", ClampMax = "300.0"))
	float FoodRespawnTime {10.f};
};