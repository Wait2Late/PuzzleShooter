// Fill out your copyright notice in the Description page of Project Settings.


#include "NumbersGameInstance.h"

#include "PuzzleShooter/Number/NumberBlock.h"

void UNumbersGameInstance::SetNumber_Implementation(int AddNumber)
{
	bIsNumbersErased = false;
	
	StoredNumbers.Insert(AddNumber, CurrentIndex);
	CurrentIndex++;
	
	if (StoredNumbers.Num() > MaxArraySize)
		StoredNumbers.SetNum(MaxArraySize);

	if (CurrentIndex == MaxArraySize)
		StoredNumbers.SetNum(MaxArraySize);

	if (CurrentIndex > MaxArraySize)
		C_Implementation();

	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Black,
		FString::Printf(TEXT("Current Index: %d"), CurrentIndex));
}

void UNumbersGameInstance::C_Implementation()
{
	CurrentIndex = 0;
	StoredNumbers.SetNum(MaxArraySize);
	StoredNumbers.Init(CurrentIndex, MaxArraySize);

	bIsNumbersErased = true;
	
	// UpdateNumbersUI(); //Might not need this
}



int UNumbersGameInstance::GetCurrentIndex_Implementation()
{
	return CurrentIndex;
}

bool UNumbersGameInstance::GetIsNumbersErased_Implementation()
{
	return bIsNumbersErased;
}

bool UNumbersGameInstance::IsAnswerCorrect_Implementation(bool CheckPassword)
{
	if (CheckPassword)
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Green,
			FString::Printf(TEXT("The answer is correct!")));

		UpdateZeros();
	}
	
	return CheckPassword;
}

TArray<int> UNumbersGameInstance::GetNumberArray_Implementation()
{
	return StoredNumbers;
}

void UNumbersGameInstance::BackSpace_Implementation()
{
	//TODO Might come back for later. Unsure how complex it will be?
	
	int indexBefore = CurrentIndex--;
	StoredNumbers.Insert(0, indexBefore);

	// StoredNumbers.Find(0, indexBefore);
	// StoredNumbers.Contains(0);
	// StoredNumbers.RemoveAt(0);
}