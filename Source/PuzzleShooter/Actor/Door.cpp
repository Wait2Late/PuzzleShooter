// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"

#include "Components/TimelineComponent.h"
#include "PuzzleShooter/Game Instance/NumbersGameInstance.h"


// Sets default values
ADoor::ADoor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// void ADoor::ReversingTimeline(UTimelineComponent DoorTimeline)
// {
// 	UNumbersGameInstance* NumberGI = GetWorld()->GetGameInstance<UNumbersGameInstance>();
//
// 	ELevelZoneType CurrentLevelZone = IGameInstanceInterface::Execute_GetLevelZone(NumberGI);
//
// 	if (CurrentLevelZone != DoorLevelZone)
// 	{
// 		DoorTimeline.Reverse();
// 	}
// 	
// }


