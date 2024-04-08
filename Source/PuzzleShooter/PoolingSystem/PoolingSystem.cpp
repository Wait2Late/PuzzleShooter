// Fill out your copyright notice in the Description page of Project Settings.


#include "PoolingSystem.h"

#include "PuzzleShooter/Enemy/EnemyBase.h"


// Sets default values
APoolingSystem::APoolingSystem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APoolingSystem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APoolingSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


APoolingActorBase* APoolingSystem::SpawnActor(FVector SpawnLocation)
{
	for (APoolingActorBase* SpawnedActor : PoolingActors)
	{
		const bool IsActive = SpawnedActor->IsActive();
		
		if (SpawnedActor != nullptr && SpawnedActor->IsActive() == false)
		{
			SpawnedActor->TeleportTo(SpawnLocation, FRotator::ZeroRotator);
			// SpawnedActor->SetLifeSpan(PooledLifeSpan); //If I desire a lifespan like pooled bullets.
			SpawnedActor->SetActive(true);
			SpawnedActorIndex.Add(SpawnedActor->GetPoolIndex());

			return SpawnedActor;
		}
	}
	if (SpawnedActorIndex.Num() > 0)
	{
		const int PooledIndex = SpawnedActorIndex[0];
		SpawnedActorIndex.Remove(PooledIndex);
		APoolingActorBase* SpawnedActor = PoolingActors[PooledIndex];

		if (SpawnedActor != nullptr)
		{
			SpawnedActor->TeleportTo(SpawnLocation, FRotator::ZeroRotator);
			// SpawnedActor->SetLifeSpan(PooledLifeSpan); //If I desire a lifespan like pooled bullets.
			SpawnedActor->SetActive(true);
			SpawnedActorIndex.Add(SpawnedActor->GetPoolIndex());

			return SpawnedActor;
		}
	}

	return nullptr;
}

APoolingActorBase* APoolingSystem::OnBeginPool()
{
	
	if (PoolingActor != nullptr)
	{
		for (int i = 0; i < PoolSize; ++i)
		{
			APoolingActorBase* PoolsActor = GetWorld()->SpawnActor<APoolingActorBase>(PoolingActor, PoolLocation, FRotator::ZeroRotator);
			if (PoolsActor != nullptr)
			{
				PoolsActor->SetActive(false);
				PoolsActor->SetPoolIndex(i);
				// PoolsActor->OnPoolingActorDespawn.AddDynamic(this, &APoolingSystem::OnPoolingActorDespawn);
				PoolsActor->OnEnemyTypeDespawn.AddDynamic(this, &APoolingSystem::OnPoolingActorDespawn);

				PoolingActors.Add(PoolsActor);
			}
		}
	}
	return nullptr;
}

void APoolingSystem::OnPoolingActorDespawn(APoolingActorBase* PoolingActorBase, EEnemyType Enemy)
{
	TEnumAsByte CurrentEnemy = Enemy;
	SpawnedActorIndex.Remove(PoolingActorBase->GetPoolIndex());
}

// void APoolingSystem::OnPoolingEnemyDespawn(APoolingActorBase* PoolingActorBase, EEnemyType Enemy)
// {
	
// }


int APoolingSystem::GetPoolSize() const
{
	return PoolSize;
}
