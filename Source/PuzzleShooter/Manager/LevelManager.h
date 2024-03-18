// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleShooter/Enum/LevelZoneType.h"
#include "LevelManager.generated.h"

UCLASS()
class PUZZLESHOOTER_API ALevelManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALevelManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "LevelZone Category")
	TEnumAsByte<ELevelZoneType> LevelZoneType;

	UFUNCTION(BlueprintCallable)
	bool PasswordIsValid(TArray<int> LevelPassword);
	
};
