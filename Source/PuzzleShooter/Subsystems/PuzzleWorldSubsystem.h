// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuzzleShooter/Manager/WaveManager/WaveManager.h"
#include "Subsystems/WorldSubsystem.h"
#include "PuzzleWorldSubsystem.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInitializeEnemySpawnLocations);
/**
 * 
 */
UCLASS()
class PUZZLESHOOTER_API UPuzzleWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	
	FOnInitializeEnemySpawnLocations OnInitializeEnemySpawnLocations;
	
	UFUNCTION(BlueprintCallable)
	void DoSomething();

	UFUNCTION(BlueprintCallable)
	void OnInstantiateWaveManager(TSubclassOf<AWaveManager> WaveManager);
	
};
