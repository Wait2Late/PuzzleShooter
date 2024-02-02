// Copyright Epic Games, Inc. All Rights Reserved.

#include "PuzzleShooterGameMode.h"
#include "PuzzleShooterCharacter.h"
#include "UObject/ConstructorHelpers.h"

APuzzleShooterGameMode::APuzzleShooterGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
