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
	OnClearedLevel.Clear();
	OnReachedNewLevel.Clear();
	
}

void ULevelZoneSubsystem::SetLevelZone(const ELevelZoneType NewLevelZone)
{
	CurrentLevelZone = NewLevelZone;
}

void ULevelZoneSubsystem::TriggerReachedNewLevel() const
{
	OnReachedNewLevel.Broadcast();
}

void ULevelZoneSubsystem::TriggerClearedLevel() const
{
	OnClearedLevel.Broadcast(CurrentLevelZone);
}

