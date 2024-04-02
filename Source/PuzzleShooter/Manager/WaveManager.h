// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
// #include "GameFramework/Info.h" // Might revert to AInfo again.
#include "GameFramework/Actor.h"
#include "PuzzleShooter/Enemy/EnemyBase.h"
#include "PuzzleShooter/Struct/EnemyWave.h"
#include "WaveManager.generated.h"

UCLASS()
class PUZZLESHOOTER_API AWaveManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWaveManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly, Category= "WaveManager Category")
	int CurrentWaveIndex = 0;
	
	UPROPERTY(BlueprintReadOnly, Category = "WaveManager Category")
	int RemainingEnemiesAmount = 0;

	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SpawnWave Category")
	// FEnemyWave Waves;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SpawnWave Category")
	float SpawnOffsetZ = 75.f;

private:
	void RemoveDeadEnemy(AEnemyBase* EnemyBase, EEnemyType Enemy);

	FVector GetRandomLocationAroundPLayer() const;

	
};
