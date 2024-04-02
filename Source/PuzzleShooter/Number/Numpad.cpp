// Fill out your copyright notice in the Description page of Project Settings.


#include "Numpad.h"

#include "EngineUtils.h"
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


void ANumpad::OnInitializeSetAllChildrenLevelZone() const
{
	// TArray<AActor*> OutActors;
	// TArray<AActor*> ChildActors;
	// GetAllChildActors(ChildActors);
	//
	// const TSubclassOf<ANumberBlock> NumberBlock;
	//
	// UGameplayStatics::GetAllActorsOfClass(GetWorld(), NumberBlock, OutActors);
	//
	
	// for (const auto* OutActor : OutActors)
	// {
	// 	for (const auto* OutChildActor : ChildActors)
	// 	{
	// 		if (OutChildActor == OutActor)
	// 		{
	// 			OutActor->SetLevelZone(this->LevelZone);
	// 		}
	// 	}
	// }


	// for(TActorIterator<ANumberBlock> BlockItr(GetWorld()); BlockItr; ++BlockItr)
	// {
	// 	if (BlockItr && *BlockItr)
	// 	{
	// 		auto* CurrentBlock = *BlockItr;
	//
	// 		auto level = CurrentBlock->LevelZone;
	// 	}
	// }

	for (ANumberBlock* Block : TActorRange<ANumberBlock>(GetWorld()))
		if (Block->GetParentActor() == this)
			Block->SetLevelZone(this->LevelZone);

	// TArray<ANumberBlock> Blocks;
	// for (int i = 0; i < ChildActors.Num(); ++i)
	// {
	// 	if (ChildActors[i]->IsChildActor())
	// 	{
	// 		Blocks.Add(ChildActors[i]->Get)
	// 	}
	//
	// 	// if (IsChildActor() == ChildActors[i]->Children)
	// 	// {
	// 		
	// 	// }
	// 	// OutActors[i]->LevelZone
	// }
}

