// Fill out your copyright notice in the Description page of Project Settings.


#include "NumbersGameInstance.h"

void UNumbersGameInstance::SetNumber_Implementation(int AddNumber)
{
	///

	StoredNumbers.RemoveAt(4);
	StoredNumbers.Insert(AddNumber,0);
}

TArray<int> UNumbersGameInstance::GetNumberArray_Implementation()
{
	return StoredNumbers;
}

void UNumbersGameInstance::C_Implementation()
{
	StoredNumbers.Init(0, 5);
	StoredNumbers.SetNum(5);
}

void UNumbersGameInstance::BackSpace_Implementation()
{
	StoredNumbers.RemoveAt(0);
	StoredNumbers.Insert(0, 0);
}

