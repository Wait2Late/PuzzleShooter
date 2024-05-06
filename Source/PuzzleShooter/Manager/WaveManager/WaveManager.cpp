// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveManager.h"

#include "EngineUtils.h"
#include "NavigationSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "PuzzleShooter/Subsystems/LevelZoneSubsystem.h"
#include "PuzzleShooter/Subsystems/PuzzleWorldSubsystem.h"


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

	OnInitializePools();

	const TObjectPtr<UPuzzleWorldSubsystem> PuzzleWorld = GetWorld()->GetSubsystem<UPuzzleWorldSubsystem>();
	if (PuzzleWorld != nullptr)
		PuzzleWorld->OnInitializeEnemySpawnLocations.AddDynamic(this, &AWaveManager::AddSpawnLocations);
}

// Called every frame
void AWaveManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// void AWaveManager::RemoveDeadEnemy(APoolingActorBase* PoolingActor)
// {
// 	RemainingEnemiesAmount -= 1;
// 	UE_LOG(LogTemp, Warning, TEXT("Remainging Enemies: %d"), RemainingEnemiesAmount);
// 	PoolingActor->OnPoolingActorDespawn.RemoveDynamic(this, &AWaveManager::RemoveDeadEnemy); 
// 	
// 	CurrentWaveEnemies.Remove(PoolingActor);
// 	CurrentWaveEnemies.Shrink();
// }

void AWaveManager::RemoveEnemyType(APoolingActorBase* PoolingActorBase, const EEnemyType Enemy)
{
	RemainingEnemiesAmount -= 1;
	UE_LOG(LogTemp, Warning, TEXT("Remainging Enemies: %d"), RemainingEnemiesAmount);
	// PoolingActorBase->OnPoolingActorDespawn.RemoveDynamic(this, &AWaveManager::RemoveDeadEnemy);
	PoolingActorBase->OnEnemyTypeDespawn.RemoveDynamic(this, &AWaveManager::RemoveEnemyType);

	const TEnumAsByte CurrentEnemyType = Enemy;
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red,
		FString::Printf(TEXT("EnemyType: %d"), CurrentEnemyType.GetIntValue()));
	
	switch (CurrentEnemyType)
	{
		case EEnemyType::MeleeEnemy:
			AmountOfMeleeEnemies.Remove(PoolingActorBase);
			AmountOfMeleeEnemies.Shrink();
		break;
		case EEnemyType::RangedEnemy:
			AmountOfRangedEnemies.Remove(PoolingActorBase);
			AmountOfRangedEnemies.Shrink();
		break;
		case EEnemyType::None:
		default: break;
	}
	
	CurrentWaveEnemies.Remove(PoolingActorBase);
	CurrentWaveEnemies.Shrink();

}

void AWaveManager::SpawnWave()
{
	if (MaxEnemies >= CurrentWaveEnemies.Num())
	{
 
		const EEnemyType CurrentEnemyType = EnemyType;
		
		for (int j = 0; j < AmountOfEnemiesToSpawn; j++)
		{
			if (MaxEnemies <= CurrentWaveEnemies.Num())
			{
				GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Yellow, TEXT("Max amount of enemies. Not allowed to spawn more!"));	
				break;
			}

			const FVector SpawnOnRandomLocations = GetRandomLocationAroundPLayer();
			// UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), SpawnVfx, SpawnOnRandomLocations);
			// OnSpawnVFX(SpawnOnRandomLocations);
			

			TObjectPtr<APoolingActorBase> CurrentEnemy = EnemyPools[CurrentEnemyType]->SpawnActor(SpawnOnRandomLocations);//spawns randomly around the player

			// TObjectPtr<AEnemyBase> currentEnemy = Cast<AEnemyBase>(CurrentEnemy);
			if(CurrentEnemy == nullptr)
			{
				continue;
			}

			// CurrentEnemy->OnPoolingActorDespawn.AddDynamic(this, &AWaveManager::RemoveDeadEnemy); //OG

			CurrentEnemy->OnEnemyTypeDespawn.AddDynamic(this, &AWaveManager::RemoveEnemyType);

			switch (CurrentEnemyType)
			{
				case EEnemyType::MeleeEnemy: AmountOfMeleeEnemies.Add(CurrentEnemy); break;
				case EEnemyType::RangedEnemy: AmountOfRangedEnemies.Add(CurrentEnemy); break;
				case EEnemyType::None:
					default: break;
			}

			CurrentWaveEnemies.Add(CurrentEnemy);
			RemainingEnemiesAmount += 1;
			
		}
		CurrentWaveIndex += 1;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow,
			FString::Printf(TEXT("else it's full")));
	}
}

void AWaveManager::AddSpawnLocations()
{
	
	for (const TObjectPtr<AEnemySpawnLocation> SpawnLocation : TActorRange<AEnemySpawnLocation>(GetWorld()))
	{
		switch (SpawnLocation->LevelZone)
		{
		case ELevelZoneType::Level_0: Level_0_SpawnLocations.Add(SpawnLocation->GetTransform()); break;
		case ELevelZoneType::Level_1: Level_1_SpawnLocations.Add(SpawnLocation->GetTransform()); break;
		case ELevelZoneType::Level_2: Level_2_SpawnLocations.Add(SpawnLocation->GetTransform()); break;
		case ELevelZoneType::Level_3: Level_3_SpawnLocations.Add(SpawnLocation->GetTransform()); break;
		case ELevelZoneType::Level_4: Level_4_SpawnLocations.Add(SpawnLocation->GetTransform()); break;
		default: GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Black,
			FString::Printf("Need more Level enums"));
			break;
		}
	}

	const TObjectPtr<UPuzzleWorldSubsystem> PuzzleWorld = GetWorld()->GetSubsystem<UPuzzleWorldSubsystem>();
	if (PuzzleWorld != nullptr)
		PuzzleWorld->OnInitializeEnemySpawnLocations.Clear();
	
}





void AWaveManager::RepopulateAvailableSpawnLocations()
{
	const TObjectPtr<ULevelZoneSubsystem> LevelZoneSubsystem = GetGameInstance()->GetSubsystem<ULevelZoneSubsystem>();
	
	switch (LevelZoneSubsystem->CurrentLevelZone)
	{
		case ELevelZoneType::Level_0:
			CurrentSpawnLocations.Empty();
			CurrentSpawnLocations.Append(Level_0_SpawnLocations);
			break;
		case ELevelZoneType::Level_1:
			CurrentSpawnLocations.Empty();
			CurrentSpawnLocations.Append(Level_1_SpawnLocations);
			break;
		case ELevelZoneType::Level_2:
			CurrentSpawnLocations.Empty();
			CurrentSpawnLocations.Append(Level_2_SpawnLocations);
			break;
		case ELevelZoneType::Level_3:
			CurrentSpawnLocations.Empty();
			CurrentSpawnLocations.Append(Level_3_SpawnLocations);
			break;
		case ELevelZoneType::Level_4:
			CurrentSpawnLocations.Empty();
			CurrentSpawnLocations.Append(Level_4_SpawnLocations);
			break;
		default: break;

	}
	
	// AvailableSpawnLocations.Append(SpawnLocations); //OG
}

FTransform AWaveManager::GetAvailableSpawnPosition()
{
	FTransform SpawnPosition;

	if (CurrentSpawnLocations.Num() > 0)
	{
		SpawnPosition = CurrentSpawnLocations[0];
		CurrentSpawnLocations.RemoveAt(0);

		return SpawnPosition;
	}
	else
	{
		return SpawnPosition;
	}
	
	////OG	
	// FTransform SpawnPos;
	//
	// if(AvailableSpawnLocations.Num() > 0)
	// {
	// 	SpawnPos = AvailableSpawnLocations[0];
	// 	AvailableSpawnLocations.RemoveAt(0);
	//
	// 	return SpawnPos;	
	// }
	// else
	// {
	// 	return SpawnPos;
	// }
}

void AWaveManager::OnInitializePools()
{
	for (const auto Pool : EnemyPools)
		Pool.Value->OnBeginPool();
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

// void AWaveManager::PopulateSpawnLocations()
// {
// 	TArray<AActor*> OutActors;
// 	UGameplayStatics::GetAllActorsOfClass(GetWorld(), SpawnLocationReference, OutActors);
//
// 	for (int i = 0; i < OutActors.Num(); i++)
// 	{
// 		SpawnLocations.Add(OutActors[i]->GetTransform());
// 	}
//
// 	RepopulateAvailableSpawnLocations();
// }
