﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleShooter/Enum/LevelZoneType.h"
#include "Numpad.generated.h"

UCLASS()
class PUZZLESHOOTER_API ANumpad : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ANumpad();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ELevelZoneType> LevelZone;

private:
	
	UFUNCTION()
	void OnInitializeSetAllChildrenLevelZone() const;


	
	
};
