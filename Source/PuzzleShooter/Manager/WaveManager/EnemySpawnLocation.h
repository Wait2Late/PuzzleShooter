// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleShooter/Enum/LevelZoneType.h"
#include "PuzzleShooter/Interface/OnInitializeLevelZones.h"
#include "EnemySpawnLocation.generated.h"

UCLASS()
class PUZZLESHOOTER_API AEnemySpawnLocation : public AActor, public IOnInitializeLevelZones
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemySpawnLocation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintCallable)
	virtual void SetLevelZone_Implementation(const ELevelZoneType NewLevelZone) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TEnumAsByte<ELevelZoneType> LevelZone;
private:

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Display Enemy Spawn Location")
	FVector EnemySpawnLocation;
	
};
