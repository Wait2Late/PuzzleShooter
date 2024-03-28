// Fill out your copyright notice in the Description page of Project Settings.


#include "TestWorldSubsystem.h"

#include "PuzzleShooter/Manager/WaveManager.h"

void UTestWorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UTestWorldSubsystem::Deinitialize()
{
	Super::Deinitialize();
	
}

void UTestWorldSubsystem::DoSomething()
{
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Emerald,
		FString::Printf(TEXT("Hello WorldSubsystem!")));
}

void UTestWorldSubsystem::OnInstantiateWaveManager(TSubclassOf<AWaveManager> WaveManager)
{
	// const TSubclassOf<AWaveManager> WaveManager;
	GetWorld()->SpawnActor<AWaveManager>(WaveManager, FVector::ZeroVector, FRotator::ZeroRotator);
}
