// Fill out your copyright notice in the Description page of Project Settings.


#include "NumbersGameInstance.h"

void UNumbersGameInstance::SetNumber_Implementation(int AddNumber)
{
	StoredNumbers.RemoveAt(StoredNumbers.Max() - 1);
	StoredNumbers.Insert(AddNumber,0);

	CheckPassword();
}

TArray<int> UNumbersGameInstance::GetNumberArray_Implementation()
{
	return StoredNumbers;
}

void UNumbersGameInstance::C_Implementation()
{
	StoredNumbers.SetNum(5);
	StoredNumbers.Init(0, 5);
}

void UNumbersGameInstance::BackSpace_Implementation()
{
	//Might come back for later. Unsure how complex it will be?
	int index;
	StoredNumbers.Find(0, index);
	StoredNumbers.Contains(0);
	
	
	StoredNumbers.RemoveAt(0);
	StoredNumbers.Insert(0, 0);
}

