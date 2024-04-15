// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuzzleShooter/Enum/LevelZoneType.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LevelZoneSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelZoneCleared, ELevelZoneType, ClearedLevelZone);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNewLevelZoneReached);

UCLASS(BlueprintType)
class PUZZLESHOOTER_API ULevelZoneSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	
	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<ELevelZoneType> CurrentLevelZone;

	UFUNCTION(BlueprintCallable)
	void SetLevelZone(ELevelZoneType NewLevelZone);


	//Delegates
	UPROPERTY(BlueprintAssignable, meta = (DisplayName = "OnNewLevelZoneReached"), Category="Level Zone Subsystem Events")
	FOnNewLevelZoneReached OnNewLevelZoneReached;
	UPROPERTY(BlueprintAssignable, meta = (DisplayName = "OnLevelCleared"), Category="Level Zone Subsystem Events")
	FOnLevelZoneCleared OnLevelZoneCleared;

	UFUNCTION(BlueprintCallable, Category= "LevelZone Subsystem Functions")
	void TriggerNewLevelZoneReached();
	UFUNCTION(BlueprintCallable, Category= "LevelZone Subsystem Functions")
	void TriggerLevelZoneCleared();
	
private:
	
};
