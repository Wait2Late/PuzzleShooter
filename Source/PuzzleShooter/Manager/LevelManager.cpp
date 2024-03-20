// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelManager.h"

#include "PuzzleShooter/Game Instance/NumbersGameInstance.h"


// Sets default values
ALevelManager::ALevelManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALevelManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ALevelManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ALevelManager::IsPasswordValid(TArray<int> LevelPassword)
{
	UNumbersGameInstance* NumberGI = GetWorld()->GetGameInstance<UNumbersGameInstance>();

	TArray<int> StoredNumbers = IGameInstanceInterface::Execute_GetNumberArray(NumberGI);

	if (LevelPassword.Num() != StoredNumbers.Num())
		return false;

	for (int i = 0; i < LevelPassword.Num(); ++i)
	{
		if (LevelPassword[i] != StoredNumbers[i])
			return false;
	}

	// const bool AnswerIsCorrect = IGameInstanceInterface::Execute_IsAnswerCorrect(NumberGI, true);
	
	GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Green,
		FString::Printf(TEXT("The answer is correct!")));
	return true;
}

