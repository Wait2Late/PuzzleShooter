// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleWorldSubsystem.h"

void UPuzzleWorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UPuzzleWorldSubsystem::Deinitialize()
{
	Super::Deinitialize();
	
}

void UPuzzleWorldSubsystem::DoSomething()
{
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Emerald,
		FString::Printf(TEXT("Hello WorldSubsystem!")));
}

void UPuzzleWorldSubsystem::OnInstantiateWaveManager(const TSubclassOf<AWaveManager> WaveManager)
{
	// const TSubclassOf<AWaveManager> WaveManager;
	GetWorld()->SpawnActor<AWaveManager>(WaveManager, FVector::ZeroVector, FRotator::ZeroRotator);
}
