﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "PuzzleWorldSubsystem.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInitializeEnemySpawnLocations);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAddNewPasswordHint, int, PasswordHint);
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

	//Delegate EVENTS
	UPROPERTY(BlueprintAssignable, Category= "Puzzle World Subsystem Events")
	FOnInitializeEnemySpawnLocations OnInitializeEnemySpawnLocations;
	UPROPERTY(BlueprintAssignable, Category= "Puzzle World Subsystem Events")
	FOnAddNewPasswordHint OnAddNewPasswordHint;
	

	UFUNCTION(BlueprintCallable)
	void UpdatePasswordHints(int PasswordHint);

};