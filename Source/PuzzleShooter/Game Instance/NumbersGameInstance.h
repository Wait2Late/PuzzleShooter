// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PuzzleShooter/Interface/GameInstanceInterface.h"
#include "NumbersGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLESHOOTER_API UNumbersGameInstance : public UGameInstance, public IGameInstanceInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	TArray<int> StoredNumbers;
	// UPROPERTY(BlueprintReadWrite)
	// TEnumAsByte<ELevelZoneType> CurrentLevelZone;
	UPROPERTY(BlueprintReadOnly)
	bool bIsNumbersErased;

	UFUNCTION(BlueprintCallable, Blueprintable)
	virtual void SetNumber_Implementation(int AddNumber) override;
	UFUNCTION(BlueprintCallable, Blueprintable)
    virtual TArray<int> GetNumberArray_Implementation() override;
	UFUNCTION(BlueprintCallable, Blueprintable)
	virtual void C_Implementation() override;
	UFUNCTION(BlueprintCallable, Blueprintable)
	virtual void BackSpace_Implementation() override;
	UFUNCTION(BlueprintCallable, Blueprintable)
	virtual int GetCurrentIndex_Implementation() override;
	UFUNCTION(BlueprintCallable, Blueprintable)
	virtual bool GetIsNumbersErased_Implementation() override;
	// UFUNCTION(BlueprintCallable, Blueprintable)
	// virtual ELevelZoneType GetLevelZone_Implementation() override;
	// UFUNCTION(BlueprintCallable, Blueprintable)
	// virtual void SetLevelZone_Implementation(ELevelZoneType SetLevelZone) override;
	UFUNCTION(BlueprintCallable, Blueprintable)
	virtual bool IsAnswerCorrect_Implementation(bool CheckPassword) override;
	
	
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateNumbersUI();
	UFUNCTION(BlueprintImplementableEvent, Blueprintable)
	void UpdateZeros();
private:
	int CurrentIndex = 0;
	const int MaxArraySize = 5;
};
