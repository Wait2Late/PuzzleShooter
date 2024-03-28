#pragma once

#include "CoreMinimal.h"
// #include "EnemyTowardsSpawn.h"
#include "PuzzleShooter/Enum/EnemyType.h"
#include "EnemyWave.generated.h"

USTRUCT(BlueprintType)
struct FEnemyWave
{
	GENERATED_BODY()

	FEnemyWave();
	~FEnemyWave();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "EnemyWaves Category") // Might not need this
	TArray<TEnumAsByte<EEnemyType>> EnemiesToSpawn;
	
	
};
