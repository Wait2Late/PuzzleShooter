﻿// Fill out your copyright notice in the Description page of Project Settings.

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

	UFUNCTION(BlueprintCallable, Blueprintable)
	virtual void SetNumber_Implementation(int AddNumber) override;
	UFUNCTION(BlueprintCallable, Blueprintable)
    virtual TArray<int> GetNumberArray_Implementation() override;

	virtual void WhateverVoid_Implementation() override
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Black,
			FString::Printf(TEXT("Whatever")));
	}


	
};
