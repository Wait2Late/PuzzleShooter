// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuzzleShooter/Enum/LevelZoneType.h"
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

	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetNumber(int AddNumber);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	TArray<int> GetNumberArray();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void C();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void BackSpace();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	int GetCurrentIndex();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool GetIsNumbersErased();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	ELevelZoneType GetLevelZone();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetLevelZone(ELevelZoneType SetLevelZone);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool IsAnswerCorrect(bool CheckPassword);
};
