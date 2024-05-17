// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
// #include "GameFramework/Info.h" // Might revert to AInfo again.
#include "EnemySpawnLocation.h"
#include "GameFramework/Actor.h"
#include "PuzzleShooter/Enum/LevelZoneType.h"
#include "PuzzleShooter/PoolingSystem/PoolingSystem.h"
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "WaveManager Category")
	int CurrentWaveIndex = 0;
	UPROPERTY(BlueprintReadOnly, Category = "WaveManager Category")
	int RemainingEnemiesAmount = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SpawnWave Category")
	FEnemyWave Waves;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SpawnWave Category")
	float SpawnOffsetZ = 75.f;
	UPROPERTY(EditAnywhere, Category="SpawnWave Category")
	TSubclassOf<AEnemySpawnLocation> SpawnLocationReference;


	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<APoolingActorBase>> AmountOfMeleeEnemies;
	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<APoolingActorBase>> AmountOfRangedEnemies;
	UPROPERTY(BlueprintReadOnly)
	TArray<TObjectPtr<APoolingActorBase>> CurrentWaveEnemies; //OG

	UPROPERTY(EditAnywhere, Category="SpawnWave Category")
	TMap<TEnumAsByte<EEnemyType>, TObjectPtr<APoolingSystem>> EnemyPools;


	UPROPERTY(BlueprintReadWrite, Category= "SpawnWave Category")
	int MeleeEnemies;
	UPROPERTY(BlueprintReadWrite, Category= "SpawnWave Category")
	int RangedEnemies;
	UPROPERTY(BlueprintReadWrite, Category= "SpawnWave Category")
	ELevelZoneType LevelZone;

	
	UFUNCTION()
	void RemoveEnemyType(APoolingActorBase* PoolingActorBase, const EEnemyType Enemy);
protected:
	UFUNCTION(BlueprintCallable)
	void SpawnWave();

	UFUNCTION(BlueprintImplementableEvent)
	void OnePasswordNumber(int PasswordNumber);
public:
	//TODO Might not need this, but still going to experiment
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Spawn Locations")
	TArray<FTransform> Level_0_SpawnLocations;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Spawn Locations")
	TArray<FTransform> Level_1_SpawnLocations;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Spawn Locations")
	TArray<FTransform> Level_2_SpawnLocations;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Spawn Locations")
	TArray<FTransform> Level_3_SpawnLocations;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Spawn Locations")
	TArray<FTransform> Level_4_SpawnLocations;

private:
	
	TArray<int> CurrentPassword;
	
	UFUNCTION(BlueprintCallable)
	void UpdatePassword(TArray<int> Password);
	int GetOnePasswordNumber();


	
	TArray<FTransform> CurrentSpawnLocations;
	TArray<TArray<FTransform>> SpawnLocation_LevelZone;
	
	UFUNCTION()
	void AddSpawnLocations();
	UFUNCTION()
	void RepopulateAvailableSpawnLocations();
	FTransform GetAvailableSpawnPosition();
	void AppendNewSpawnLocations(const TArray<FTransform>& SpawnLocations);


	
	void OnInitializePools();
	FVector GetRandomLocationAroundPLayer() const;
};
