// Fill out your copyright notice in the Description page of Project Settings.


#include "NumbersGameInstance.h"

void UNumbersGameInstance::SetNumber_Implementation(int AddNumber)
{
	StoredNumbers.Add(AddNumber);
	
	if (StoredNumbers.Num() > 5)
	{
		StoredNumbers.RemoveAt(0);
		// StoredNumbers.Shrink();
	}

}

TArray<int> UNumbersGameInstance::GetNumberArray_Implementation()
{
	return StoredNumbers;
}

void UNumbersGameInstance::C_Implementation()
{
	StoredNumbers.Empty();

	if (StoredNumbers.IsEmpty())
	{
		for (int i = 0; i < 5; ++i)
			SetNumber_Implementation(0);
	}
	
}

void UNumbersGameInstance::BackSpace_Implementation()
{
	StoredNumbers.RemoveAt(0);
	// SetNumber_Implementation(0);
}
