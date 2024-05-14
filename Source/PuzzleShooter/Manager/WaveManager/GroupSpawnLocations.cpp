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


	// for (TActorIterator<AEnemySpawnLocation> SpawnIterator(GetWorld()); SpawnIterator; ++SpawnIterator)
		// if (SpawnIterator->GetAttachParentActor() == this)
			// SpawnIterator->SetLevelZone(this->LevelZone);
	
	// const TObjectPtr<UPuzzleWorldSubsystem> PuzzleWorldSubsystem = GetWorld()->GetSubsystem<UPuzzleWorldSubsystem>();
	// PuzzleWorldSubsystem->OnInitializeEnemySpawnLocations.Broadcast();

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AGroupSpawnLocations::BroadCastLater, 0.1f);
}

//TODO Why does this need to be delayed?
void AGroupSpawnLocations::BroadCastLater() const 
{
	const TObjectPtr<UPuzzleWorldSubsystem> PuzzleWorldSubsystem = GetWorld()->GetSubsystem<UPuzzleWorldSubsystem>();
	PuzzleWorldSubsystem->OnInitializeEnemySpawnLocations.Broadcast();
}


