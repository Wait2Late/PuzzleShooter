// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameInstanceInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UGameInstanceInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PUZZLESHOOTER_API IGameInstanceInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	
	TArray<int> NumberCode;

	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetNumber(int AddNumber);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	TArray<int> GetNumber();
	
	
	
	// virtual TArray<int> GetNumbers(){ return NumberCode; }

	
	// int GetNumbers(){ return }
	
};
