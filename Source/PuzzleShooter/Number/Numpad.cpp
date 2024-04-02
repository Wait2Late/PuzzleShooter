// Fill out your copyright notice in the Description page of Project Settings.


#include "Numpad.h"
#include "NumberBlock.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ANumpad::ANumpad()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ANumpad::BeginPlay()
{
	Super::BeginPlay();
	OnInitializeSetAllChildrenLevelZone();
	
}

// Called every frame
void ANumpad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

ELevelZoneType ANumpad::GetLevelZone()
{
	return LevelZone;
}

void ANumpad::OnInitializeSetAllChildrenLevelZone()
{
	TArray<AActor*> OutActors;
	TArray<AActor*> ChildActors;

	const TSubclassOf<ANumberBlock> NumberBlock;
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), NumberBlock, OutActors);

	ANumberBlock block;
	
	GetAllChildActors(ChildActors);



	for (int i = 0; i < ChildActors.Num(); ++i)
	{
		// if (IsChildActor() == ChildActors[i]->Children)
		// {
			
		// }
		// OutActors[i]->LevelZone
	}

	int LocalInt = ChildActors.Num();
	
	for (const AActor* OutActor : OutActors)
	{
		for (const AActor* OutChildActor : ChildActors)
		{
			// if (OutChildActor == OutActor)
			// {
			// 	block.SetLevelZone(this->LevelZone);
			// }
		}
	}
}

