// Fill out your copyright notice in the Description page of Project Settings.


#include "PoolingActorBase.h"

#include "AI/NavigationSystemBase.h"
#include "GameFramework/DefaultPawn.h"
#include "GameFramework/PawnMovementComponent.h"


// Sets default values
APoolingActorBase::APoolingActorBase()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void APoolingActorBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APoolingActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APoolingActorBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APoolingActorBase::Deactivate()
{
	GetWorldTimerManager().ClearAllTimersForObject(this);
	// OnPoolingActorDespawn.Broadcast(this);
	OnEnemyTypeDespawn.Broadcast(this, EnemyType);
	SetActive(false);
}

void APoolingActorBase::SetActive(bool IsActive)
{
	bIsActive = IsActive;
	if (!IsActive)
	{
		OnSetActiveCalled(IsActive);

		SetActorHiddenInGame(IsActive);
		SetActorTickEnabled(IsActive);
		SetActorEnableCollision(IsActive);

		

		// UPawnMovementComponent* MovementComponent = GetMovementComponent();
		// MovementComponent->SetComponentTickEnabled(true);
		// GetController()->GetPawn()->TurnOff();
		// MovementComponent->Deactivate();
		
	}
	if (IsActive)
	{
		SetActorHiddenInGame(!bIsActive);
		// GetCharacterMovement()->SetDefaultMovementMode();
		SetActorTickEnabled(bIsActive);
		SetActorEnableCollision(bIsActive);


		// MovementComponent->Activate();
	}
}

void APoolingActorBase::SetLifeSpan(const float LifeTime){LifeSpan = LifeTime;}

void APoolingActorBase::SetPoolIndex(const int Index){PoolIndex = Index;}

int APoolingActorBase::GetPoolIndex() const {return PoolIndex;}

bool APoolingActorBase::IsActive() const { return bIsActive;}

