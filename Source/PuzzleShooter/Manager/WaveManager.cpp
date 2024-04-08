// Fill out your copyright notice in the Description page of Project Settings.


#include "WaveManager.h"

#include "NavigationSystem.h"
#include "NiagaraFunctionLibrary.h"
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

	OnInitializePools();

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

void AWaveManager::RemoveEnemyType(APoolingActorBase* PoolingActorBase, EEnemyType Enemy)
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
			
			// const TObjectPtr<APoolingActorBase> CurrentEnemy = EnemyPools[CurrentEnemyType]->SpawnActor(SpawnOnRandomLocations);//spawns randomly around the player

			TObjectPtr<APoolingActorBase> CurrentEnemy = EnemyPools[CurrentEnemyType]->SpawnActor(SpawnOnRandomLocations);//spawns randomly around the player
			
			// if(CurrentEnemy == nullptr)
			// {
			// 	continue;
			// }

			// CurrentEnemy->OnPoolingActorDespawn.AddDynamic(this, &AWaveManager::RemoveDeadEnemy); //OG

			// APoolingActorBase* CurrentEnemy = nullptr;
			CurrentEnemy->OnEnemyTypeDespawn.AddDynamic(this, &AWaveManager::RemoveEnemyType);

			// TArray<AEnemyBase*> AEnemyBase; //TODO Why does it not respond to the children?
			// AEnemyBase.Add(CurrentEnemy);

			// APoolingSystem* PoolingSystem = nullptr;
			// APoolingActorBase* PoolingActorBase = PoolingSystem->SpawnActor(SpawnOnRandomLocations); //This is the parent of AEnemyBase
			//
			// AEnemyBase* EnemyBase = Cast<AEnemyBase>(PoolingActorBase); // Upcast to AEnemyBase
			//
			// TArray<TObjectPtr<APoolingActorBase>> CurrentEnemies; //OG
			//
			// CurrentEnemies.Add(EnemyBase);

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


void AWaveManager::OnInitializePools()
{
	for (auto Pool : EnemyPools)
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

