﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"

#include "../Interface/HitProjectile.h"


// Sets default values
AEnemyBase::AEnemyBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxComponent->SetupAttachment(StaticMeshComponent);

	

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBase::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

UBehaviorTree* AEnemyBase::GetBehaviourTree()
{
	return Tree;
}

void AEnemyBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->Implements<UHitProjectile>())
	{
		Deactivate();
		GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Red,
			FString::Printf(TEXT("Returned to Pool")));
	}



	
}

// void AEnemyBase::Deactivate()
// {
// 	// Super::Deactivate();
// 	GetWorldTimerManager().ClearAllTimersForObject(this);
// 	OnPoolingEnemyDespawn.Broadcast(this);
// 	SetActive(false);
// }


