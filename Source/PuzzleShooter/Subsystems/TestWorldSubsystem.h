// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuzzleShooter/Manager/WaveManager/WaveManager.h"
#include "Subsystems/WorldSubsystem.h"
#include "TestWorldSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLESHOOTER_API UTestWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable)
	void DoSomething();

	UFUNCTION(BlueprintCallable)
	void OnInstantiateWaveManager(TSubclassOf<AWaveManager> WaveManager);
	
};
