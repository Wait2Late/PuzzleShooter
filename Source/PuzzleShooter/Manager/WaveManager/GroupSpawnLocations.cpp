// Fill out your copyright notice in the Description page of Project Settings.


#include "GroupSpawnLocations.h"

#include "EnemySpawnLocation.h"
#include "EngineUtils.h"


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

void AGroupSpawnLocations::OnInitializeChildrenLevelZoneType()
{
	for (const TObjectPtr<AEnemySpawnLocation> SpawnLocation : TActorRange<AEnemySpawnLocation>(GetWorld()))
		if (SpawnLocation->GetAttachParentActor() == this)
			SpawnLocation->SetLevelZone(this->LevelZone);


}

