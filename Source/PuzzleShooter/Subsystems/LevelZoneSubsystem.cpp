// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelZoneSubsystem.h"

#include "PuzzleShooter/Game Instance/NumbersGameInstance.h"

void ULevelZoneSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	
	CurrentLevelZone = ELevelZoneType::Level_0;
}

void ULevelZoneSubsystem::Deinitialize()
{
	Super::Deinitialize();
	OnLevelZoneCleared.Clear();
	OnNewLevelZoneReached.Clear();
	
}

void ULevelZoneSubsystem::SetLevelZone(ELevelZoneType NewLevelZone)
{
	CurrentLevelZone = NewLevelZone;
}

void ULevelZoneSubsystem::TriggerNewLevelZoneReached()
{
	OnNewLevelZoneReached.Broadcast();
}

void ULevelZoneSubsystem::TriggerLevelZoneCleared()
{
	OnLevelZoneCleared.Broadcast(CurrentLevelZone);
}

