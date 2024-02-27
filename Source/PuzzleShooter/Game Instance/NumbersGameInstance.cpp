// Fill out your copyright notice in the Description page of Project Settings.


#include "NumbersGameInstance.h"

void UNumbersGameInstance::SetNumber_Implementation(int AddNumber)
{
	StoredNumbers.Insert(AddNumber, CurrentIndex);
	
	if (StoredNumbers.Num() > MaxArraySize)
		StoredNumbers.SetNum(MaxArraySize);
	
	CurrentIndex++;
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Black,
		FString::Printf(TEXT("Current Index: %d"), CurrentIndex));
	
	if (CurrentIndex == MaxArraySize)
	{
		StoredNumbers.SetNum(MaxArraySize);
	}
	if (CurrentIndex > MaxArraySize)
	{
		C_Implementation();
	}
}

void UNumbersGameInstance::C_Implementation()
{
	CurrentIndex = 0;
	StoredNumbers.SetNum(MaxArraySize);
	StoredNumbers.Init(CurrentIndex, MaxArraySize);
}

void UNumbersGameInstance::BackSpace_Implementation()
{
	CurrentIndex = 0;
	//TODO Might come back for later. Unsure how complex it will be?
	int index;
	StoredNumbers.Find(0, index);
	StoredNumbers.Contains(0);
	
	
	StoredNumbers.RemoveAt(0);
	StoredNumbers.Insert(0, 0);
}

TArray<int> UNumbersGameInstance::GetNumberArray_Implementation()
{
	return StoredNumbers;
}
