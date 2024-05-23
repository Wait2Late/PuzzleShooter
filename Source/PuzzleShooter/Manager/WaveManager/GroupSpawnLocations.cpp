// Fill out your copyright notice in the Description page of Project Settings.


#include "GroupSpawnLocations.h"

#include "EnemySpawnLocation.h"
#include "PuzzleShooter/Subsystems/PuzzleWorldSubsystem.h"


void AGroupSpawnLocations::PostLoad()
{
	Super::PostLoad();
}

void AGroupSpawnLocations::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	
	// const TObjectPtr<UPuzzleWorldSubsystem> PuzzleWorldSubsystem = GetWorld()->GetSubsystem<UPuzzleWorldSubsystem>();
	// PuzzleWorldSubsystem->OnInitializeEnemySpawnLocations.Broadcast();
	// PuzzleWorldSubsystem->OnInitializeEnemySpawnLocations.Clear();
}

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

	TArray<TObjectPtr<AActor>> AttachedActors;
	GetAttachedActors(AttachedActors);

	for (const TObjectPtr<AActor> AttachedActor : AttachedActors)
		if (AttachedActor->Implements<UOnInitializeLevelZones>())
			IOnInitializeLevelZones::Execute_SetLevelZone(AttachedActor, this->LevelZone);
	
	
	// TWeakObjectPtr<AEnemySpawnLocation> //TODO use this if unsure which ptr to use
	// TSharedPtr<AEnemySpawnLocation> //TODO use this when a ptr need to be shared across all things


	// BroadCastAddSpawnLocations();
	
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AGroupSpawnLocations::BroadCastLater, 0.1f);
	
}

//TODO Why does this need to be delayed?
void AGroupSpawnLocations::BroadCastLater() const 
{
	BroadCastAddSpawnLocations();
}

void AGroupSpawnLocations::BroadCastAddSpawnLocations() const
{
	const TObjectPtr<UPuzzleWorldSubsystem> PuzzleWorldSubsystem = GetWorld()->GetSubsystem<UPuzzleWorldSubsystem>();
	PuzzleWorldSubsystem->OnInitializeEnemySpawnLocations.Broadcast();
	PuzzleWorldSubsystem->OnInitializeEnemySpawnLocations.Clear();
}


