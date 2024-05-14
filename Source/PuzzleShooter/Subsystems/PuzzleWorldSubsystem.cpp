// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleWorldSubsystem.h"

void UPuzzleWorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UPuzzleWorldSubsystem::Deinitialize()
{
	Super::Deinitialize();
	
}

void UPuzzleWorldSubsystem::UpdatePasswordHints(const int PasswordHint)
{
	OnAddNewPasswordHint.Broadcast(PasswordHint);
}





