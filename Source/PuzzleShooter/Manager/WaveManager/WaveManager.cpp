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
	PuzzleWorld->OnInitializeEnemySpawnLocations.AddDynamic(this, &AWaveManager::AddSpawnLocations);

	const TObjectPtr<ULevelZoneSubsystem> LevelZoneType = GetGameInstance()->GetSubsystem<ULevelZoneSubsystem>();
	LevelZoneType->OnReachedNewLevel.AddDynamic(this, &AWaveManager::RepopulateAvailableSpawnLocations);

	// FTimerHandle TimerHandle;
	// GetWorldTimerManager().SetTimer(TimerHandle, this, &AWaveManager::AddSpawnLocations, 5);
}

// Called every frame
void AWaveManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// void AWaveManager::RemoveDeadEnemy(APoolingActorBase* PoolingActor)
// {
// 	RemainingEnemiesAmount -= 1;
// 	UE_LOG(LogTemp, Warning, TEXT("Remaining Enemies: %d"), RemainingEnemiesAmount);
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

	// if(RemainingEnemiesAmount == 0) //Might not need this
	// {
	// 	RepopulateAvailableSpawnLocations();
	//
	// 	// OnWaveDone();
	// }

}

void AWaveManager::SpawnWave()
{
	if (MaxEnemies >= CurrentWaveEnemies.Num())
	{
 
		// const EEnemyType CurrentEnemyType = EnemyType;
		
		const EEnemyType CurrentEnemyType = EEnemyType::MeleeEnemy;
		const int OnlySpawnFive = 5;

		// for (int j = 0; j < AmountOfEnemiesToSpawn; j++)
		for (int j = 0; j < OnlySpawnFive; j++)
		{
			if (MaxEnemies <= CurrentWaveEnemies.Num())
			{
				GEngine->AddOnScreenDebugMessage(-1, 4, FColor::Yellow, TEXT("Max amount of enemies. Not allowed to spawn more!"));	
				break;
			}

			
			// const FVector SpawnOnRandomLocations = GetRandomLocationAroundPLayer();
			// UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), SpawnVfx, SpawnOnRandomLocations);
			// OnSpawnVFX(SpawnOnRandomLocations);
			
			const FVector CurrentSpawnTransform = GetAvailableSpawnPosition().GetLocation();

			TObjectPtr<APoolingActorBase> CurrentEnemy = EnemyPools[CurrentEnemyType]->SpawnActor(CurrentSpawnTransform);//spawns randomly around the player

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
	SpawnLocation_LevelZone.SetNum(5);
	
	for (const TObjectPtr<AEnemySpawnLocation> SpawnLocation : TActorRange<AEnemySpawnLocation>(GetWorld()))
	{
		const TEnumAsByte<ELevelZoneType> LevelZoneType = SpawnLocation->LevelZone;
		const int LevelZoneIndex = LevelZoneType.GetIntValue();
	
		// if (SpawnLocation_LevelZone.IsEmpty())
		// 	break;
		
		switch (LevelZoneType)
		{
		case ELevelZoneType::Level_0: 
			SpawnLocation_LevelZone[LevelZoneIndex].Add(SpawnLocation->GetTransform());
			// SpawnLocation_LevelZone[0].Add(SpawnLocation->GetTransform());
			// Level_0_SpawnLocations.Add(SpawnLocation->GetTransform()); //GO back to this comment only, if worse comes
			break;
		case ELevelZoneType::Level_1: 
			SpawnLocation_LevelZone[LevelZoneIndex].Add(SpawnLocation->GetTransform());
			//SpawnLocation_LevelZone[1].Add(SpawnLocation->GetTransform());
			// Level_1_SpawnLocations.Add(SpawnLocation->GetTransform()); //GO back to this comment only, if worse comes
			break;
		case ELevelZoneType::Level_2: 
			SpawnLocation_LevelZone[LevelZoneIndex].Add(SpawnLocation->GetTransform());
			//SpawnLocation_LevelZone[2].Add(SpawnLocation->GetTransform());
			// Level_2_SpawnLocations.Add(SpawnLocation->GetTransform()); //GO back to this comment only, if worse comes
			break;
		case ELevelZoneType::Level_3: 
			SpawnLocation_LevelZone[LevelZoneIndex].Add(SpawnLocation->GetTransform());
			//SpawnLocation_LevelZone[3].Add(SpawnLocation->GetTransform());
			// Level_3_SpawnLocations.Add(SpawnLocation->GetTransform()); //GO back to this comment only, if worse comes
			break;
		case ELevelZoneType::Level_4: 
			SpawnLocation_LevelZone[LevelZoneIndex].Add(SpawnLocation->GetTransform());
			//SpawnLocation_LevelZone[4].Add(SpawnLocation->GetTransform());
			// Level_4_SpawnLocations.Add(SpawnLocation->GetTransform()); //GO back to this comment only, if worse comes
			break;
		default: GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Black,
			FString::Printf(TEXT("Need more Level enums")));
			break;
		}
	}

	if (!SpawnLocation_LevelZone.IsEmpty())
	{
		Level_0_SpawnLocations.Append(SpawnLocation_LevelZone[0]);
		Level_1_SpawnLocations.Append(SpawnLocation_LevelZone[1]);
		Level_2_SpawnLocations.Append(SpawnLocation_LevelZone[2]);
		Level_3_SpawnLocations.Append(SpawnLocation_LevelZone[3]);
		Level_4_SpawnLocations.Append(SpawnLocation_LevelZone[4]);
	}

	// const TObjectPtr<UPuzzleWorldSubsystem> PuzzleWorld = GetWorld()->GetSubsystem<UPuzzleWorldSubsystem>();
	// if (PuzzleWorld != nullptr)
	// 	PuzzleWorld->OnInitializeEnemySpawnLocations.RemoveDynamic(this, &AWaveManager::AddSpawnLocations);
	
}

void AWaveManager::RepopulateAvailableSpawnLocations()
{
	const TObjectPtr<ULevelZoneSubsystem> LevelZoneSubsystem = GetGameInstance()->GetSubsystem<ULevelZoneSubsystem>();
	const TEnumAsByte<ELevelZoneType> CurrentLevelZone = LevelZoneSubsystem->CurrentLevelZone;
	const int LevelZoneIndex = CurrentLevelZone.GetIntValue();

	
	// if (!SpawnLocation_LevelZone.IsEmpty())
	// {
		switch (CurrentLevelZone)
		{
			case ELevelZoneType::Level_0: AppendNewSpawnLocations(SpawnLocation_LevelZone[LevelZoneIndex]); break;
			// case ELevelZoneType::Level_0: AppendNewSpawnLocations(SpawnLocation_LevelZone[0]); break; 
			// case ELevelZoneType::Level_0: AppendNewSpawnLocations(Level_0_SpawnLocations); break; //OG
			case ELevelZoneType::Level_1: AppendNewSpawnLocations(SpawnLocation_LevelZone[LevelZoneIndex]); break;
			// case ELevelZoneType::Level_1: AppendNewSpawnLocations(SpawnLocation_LevelZone[1]); break; 
			// case ELevelZoneType::Level_1: AppendNewSpawnLocations(Level_1_SpawnLocations); break; //OG
			case ELevelZoneType::Level_2: AppendNewSpawnLocations(SpawnLocation_LevelZone[LevelZoneIndex]); break;
			// case ELevelZoneType::Level_2: AppendNewSpawnLocations(SpawnLocation_LevelZone[2]); break; 
			// case ELevelZoneType::Level_2: AppendNewSpawnLocations(Level_2_SpawnLocations); break; //OG
			case ELevelZoneType::Level_3: AppendNewSpawnLocations(SpawnLocation_LevelZone[LevelZoneIndex]); break;
			// case ELevelZoneType::Level_3: AppendNewSpawnLocations(SpawnLocation_LevelZone[3]); break; 
			// case ELevelZoneType::Level_3: AppendNewSpawnLocations(Level_3_SpawnLocations); break; //OG
			case ELevelZoneType::Level_4: AppendNewSpawnLocations(SpawnLocation_LevelZone[LevelZoneIndex]); break;
			// case ELevelZoneType::Level_4: AppendNewSpawnLocations(SpawnLocation_LevelZone[4]); break; 
			// case ELevelZoneType::Level_4: AppendNewSpawnLocations(Level_4_SpawnLocations); break; //OG
			default: break;
		}
	// }
	// AvailableSpawnLocations.Append(SpawnLocations); //OG
}

void AWaveManager::AppendNewSpawnLocations(const TArray<FTransform>& SpawnLocations)
{
	if(!CurrentSpawnLocations.IsEmpty())
		CurrentSpawnLocations.Empty();

	CurrentSpawnLocations.Append(SpawnLocations);
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
