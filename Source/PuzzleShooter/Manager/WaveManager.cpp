// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveManager.h"

#include "NavigationSystem.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AWaveManager::AWaveManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AWaveManager::BeginPlay()
{
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow,
		FString::Printf(TEXT("AINFO")));
}

// Called every frame
void AWaveManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWaveManager::RemoveDeadEnemy(AEnemyBase* EnemyBase, EEnemyType Enemy)
{
	RemainingEnemiesAmount -= 1;
	UE_LOG(LogTemp, Warning, TEXT("Remainging Enemies: %d"), RemainingEnemiesAmount);
	// EnemyBase->OnPooledCharacterDelegateDespawn.RemoveDynamic(this, &AWaveManager::RemoveDeadEnemyFromWave);

	// CurrentWaveEnemies.Remove(EnemyBase);
	// CurrentWaveEnemies.Shrink();
}

FVector AWaveManager::GetRandomLocationAroundPLayer() const
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return FVector::ZeroVector; 
	}
	const ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(this, 0); // Assuming 0 for the first player
	if (!PlayerCharacter)
	{
		return FVector::ZeroVector; 
	}
	const UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetCurrent(World);
	if (!NavSystem)
	{
		return FVector::ZeroVector; 
	}

	//The logic behind the enemy spawn location. 
	const float RandomAngle = FMath::RandRange(0.0f, 360.0f);
	const FVector SpawnDirection = FVector::ForwardVector.RotateAngleAxis(RandomAngle, FVector::UpVector);
	const float Radius = 500.0f;
	const FVector PlayerPosition = PlayerCharacter->GetActorLocation();
	const FVector RandomLocation = PlayerPosition + Radius * SpawnDirection;
	const FVector LocalOffSetZ = FVector(0.0f, 0.0f, SpawnOffsetZ);
	
	
	FNavLocation NavLocation;
	// Check if the random location is on the navigation mesh
	if (NavSystem->GetRandomPointInNavigableRadius(RandomLocation, Radius, NavLocation))
	{
		return NavLocation.Location + LocalOffSetZ;
	}
	else
	{
		return FVector::ZeroVector;
	}
}

