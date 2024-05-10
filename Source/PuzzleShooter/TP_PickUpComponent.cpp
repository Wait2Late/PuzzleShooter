// Copyright Epic Games, Inc. All Rights Reserved.

#include "TP_PickUpComponent.h"

#include "Subsystems/PuzzleWorldSubsystem.h"

UTP_PickUpComponent::UTP_PickUpComponent()
{
	// Setup the Sphere Collision
	SphereRadius = 32.f;

	OnComponentEndOverlap.AddDynamic(this, &UTP_PickUpComponent::OnOverlapEnd);
	
	
}

void UTP_PickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// Register our Overlap Event
	// OnComponentBeginOverlap.AddDynamic(this, &UTP_PickUpComponent::OnSphereBeginOverlap);
}

void UTP_PickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Checking if it is a First Person Character overlapping
	APuzzleShooterCharacter* Character = Cast<APuzzleShooterCharacter>(OtherActor);
	if(Character != nullptr)
	{
		// Notify that the actor is being picked up
		OnPickUp.Broadcast(Character);
		OnPickUp.RemoveAll(this);

		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
		OnComponentEndOverlap.RemoveAll(this);
	}
}

void UTP_PickUpComponent::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Checking if it is a First Person Character overlapping
	APuzzleShooterCharacter* Character = Cast<APuzzleShooterCharacter>(OtherActor);
	if(Character != nullptr)
	{
		// Notify that the actor is being picked up
		OnPickUp.Broadcast(Character);
		OnPickUp.RemoveAll(this);

		const auto PuzzleWorld = GetWorld()->GetSubsystem<UPuzzleWorldSubsystem>();
		if (PuzzleWorld != nullptr)
		{
			PuzzleWorld->OnInitializeEnemySpawnLocations.Broadcast();
			PuzzleWorld->OnInitializeEnemySpawnLocations.Clear();
			
		}
		
		
		// Unregister from the Overlap Event so it is no longer triggered
		OnComponentBeginOverlap.RemoveAll(this);
		OnComponentEndOverlap.RemoveAll(this);
	}
}
