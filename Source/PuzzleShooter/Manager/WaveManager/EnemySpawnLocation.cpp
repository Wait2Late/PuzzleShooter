// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawnLocation.h"


// Sets default values
AEnemySpawnLocation::AEnemySpawnLocation()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemySpawnLocation::BeginPlay()
{
	Super::BeginPlay();
	EnemySpawnLocation = GetActorLocation();
}

// Called every frame
void AEnemySpawnLocation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemySpawnLocation::SetLevelZone_Implementation(const ELevelZoneType NewLevelZone)
{
	LevelZone = NewLevelZone;
}

