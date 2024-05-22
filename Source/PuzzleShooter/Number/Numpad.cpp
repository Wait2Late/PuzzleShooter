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
	
	TArray<TObjectPtr<AActor>> ChildActors;
	GetAllChildActors(ChildActors);

	//Interface. Should have done this day 1.
	for (TObjectPtr<AActor> ChildActor : ChildActors)
		if (ChildActor->Implements<UOnInitializeLevelZones>())
			IOnInitializeLevelZones::Execute_SetLevelZone(ChildActor, this->LevelZone);

	// //Cast. It's casting...
	// for (TObjectPtr<AActor> ChildActor : ChildActors)
	// 	if (const TObjectPtr<ANumberBlock>  NumberBlock = Cast<ANumberBlock>(ChildActor))
	// 		NumberBlock->SetLevelZone(this->LevelZone);
	//
	// //TActorRange. This was a lot less efficient than I thought. Loops 275 times
	// for (const TObjectPtr<ANumberBlock> Block : TActorRange<ANumberBlock>(GetWorld())) 
	// 	if (Block->GetParentActor() == this)
	// 		Block->SetLevelZone(this->LevelZone);
}


