// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleShooter/Enum/LevelZoneType.h"
#include "EnemySpawnLocation.generated.h"

UCLASS()
class PUZZLESHOOTER_API AEnemySpawnLocation : public AActor
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
	void SetLevelZone(ELevelZoneType NewLevelZone);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<ELevelZoneType> LevelZone;
private:
	// UPROPERTY(EditAnywhere)
};
