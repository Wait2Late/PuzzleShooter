// Fill out your copyright notice in the Description page of Project Settings.


#include "NumberBlock.h"

#include "PuzzleShooter/PuzzleShooterProjectile.h"


// Sets default values
ANumberBlock::ANumberBlock()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMeshComponent->SetupAttachment(RootComponent);
	StaticMeshComponent->SetStaticMesh(CubeMeshRef);
	FTransform transform(FVector(1,1,1));
	StaticMeshComponent->SetWorldTransform(transform);
	
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Cube"));
	
	BoxComponent->SetBoxExtent(FVector(1,1,1));
	BoxComponent->SetupAttachment(StaticMeshComponent);

	// BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ANumberBlock::OnOverlapBegin);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ANumberBlock::OnOverlapEnd);
	
}

// Called when the game starts or when spawned
void ANumberBlock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANumberBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANumberBlock::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ANumberBlock::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	APuzzleShooterProjectile* Projectile = Cast<APuzzleShooterProjectile>(OtherActor);

	if (Projectile != nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Black, FString(TEXT("Hit")));
	}

}

