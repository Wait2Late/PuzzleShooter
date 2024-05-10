// Fill out your copyright notice in the Description page of Project Settings.


#include "GroupSpawnLocations.h"

#include "EnemySpawnLocation.h"
#include "EngineUtils.h"
#include "WaveManager.h"
#include "PuzzleShooter/Subsystems/PuzzleWorldSubsystem.h"


// Sets default values
AGroupSpawnLocations::AGroupSpawnLocations()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGroupSpawnLocations::BeginPlay()
{
	Super::BeginPlay();
	OnInitializeChildrenLevelZoneType();
	
}

// Called every frame
void AGroupSpawnLocations::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGroupSpawnLocations::OnInitializeChildrenLevelZoneType() const
{
	
	for (const TObjectPtr<AEnemySpawnLocation> SpawnLocation : TActorRange<AEnemySpawnLocation>(GetWorld()))
		if (SpawnLocation->GetAttachParentActor() == this)
			SpawnLocation->SetLevelZone(this->LevelZone);

	// const TObjectPtr<AWaveManager> WaveManager = nullptr;
	// WaveManager->AddSpawnLocations();

	// const TObjectPtr<UPuzzleWorldSubsystem> PuzzleWorld = GetWorld()->GetSubsystem<UPuzzleWorldSubsystem>();
	// if (PuzzleWorld != nullptr)
	// 	PuzzleWorld->OnInitializeEnemySpawnLocations.RemoveDynamic(this, &AWaveManager::AddSpawnLocations);
	// FTimerHandle TimerHandle;
	//
	// GetWorldTimerManager().SetTimer(TimerHandle, this, &AGroupSpawnLocations::BroadcastLater, 3);
	

}

void AGroupSpawnLocations::BroadcastLater() const
{
	
	// const TObjectPtr<UPuzzleWorldSubsystem> PuzzleWorldSubsystem = GetWorld()->GetSubsystem<UPuzzleWorldSubsystem>();
	// if (PuzzleWorldSubsystem != nullptr)
	// 	PuzzleWorldSubsystem->OnInitializeEnemySpawnLocations.Broadcast();

}

