// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleShooter/Enum/LevelZoneType.h"
#include "GroupSpawnLocations.generated.h"

UCLASS()
class PUZZLESHOOTER_API AGroupSpawnLocations : public AActor
{
public:
	virtual void PostLoad() override;

	virtual void PostInitializeComponents() override;

private:
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGroupSpawnLocations();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	void OnInitializeChildrenLevelZoneType() const;
	void BroadCastLater() const;
	void BroadCastAddSpawnLocations() const;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ELevelZoneType> LevelZone;
	
	
};
