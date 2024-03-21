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
	// OnInitializeSetAllChildrenLevelZone();
	
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

	// UNumbersGameInstance* NumberGI = GetWorld()->GetGameInstance<UNumbersGameInstance>();

	// TArray<int> StoredNumbers = IGameInstanceInterface::Execute_GetNumberArray(NumberGI);

	TArray<AActor*> OutActors;
	TArray<AActor*> ChildActors;

	const TSubclassOf<ANumberBlock> NumberBlock;
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), NumberBlock, OutActors);

	GetAllChildActors(ChildActors);

	ANumberBlock* NumBlock = NumberBlock.GetDefaultObject();
	
	for (const auto OutActor : OutActors)
	{
		for (const auto OutChildActor : ChildActors)
		{
			if (OutChildActor == OutActor)
			{
				if (OutChildActor == NumBlock)
				{
					NumBlock->LevelZone = this->LevelZone;
				}
			}
		}
	}
	
	// for (int i = 0; i < ChildActors.Num(); ++i)
	// {
	// 	if (OutActors[i] == ChildActors[i])
	// 	{
	// 		ANumberBlock* NumBlock = NumberBlock.GetDefaultObject();
	// 		NumBlock->NumBlockLevelZone = this->LevelZone;
	// 	}
	// }

	// GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Green,
	// 	FString::Printf(TEXT("The answer is correct!")));

}

