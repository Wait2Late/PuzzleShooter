// Copyright Epic Games, Inc. All Rights Reserved.

#include "PuzzleShooterProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Number/NumberBlock.h"


APuzzleShooterProjectile::APuzzleShooterProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	// CollisionComp->InitSphereRadius(10.0f);
	CollisionComp->SetSphereRadius(10.f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &APuzzleShooterProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 3.f;
}

void APuzzleShooterProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ANumberBlock* NumberBlock = Cast<ANumberBlock>(OtherActor);

	// if (NumberBlock)
	// {
	// 	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Black, FString(TEXT("Hit")));
	//
	// }
	// Only add impulse and destroy projectile if we hit a physics
	// FString OtherActorClassName = OtherActor->GetClass()->GetName();
	// GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Black, FString(TEXT("Unknown actor OtherActorClassName: ")) + OtherActorClassName);
	
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		Destroy(); 
	}
}