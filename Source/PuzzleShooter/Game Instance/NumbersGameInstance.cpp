// Fill out your copyright notice in the Description page of Project Settings.


#include "NumbersGameInstance.h"

void UNumbersGameInstance::SetNumber_Implementation(int AddNumber)
{
	StoredNumbers.Add(AddNumber);
	
	if (StoredNumbers.Num() >= 5)
	{
		StoredNumbers.RemoveAt(0);
	}

}

TArray<int> UNumbersGameInstance::GetNumberArray_Implementation()
{
	return StoredNumbers;
}
