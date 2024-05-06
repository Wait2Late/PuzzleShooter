// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuzzleShooter/Enum/LevelZoneType.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "LevelZoneSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnClearedLevel, ELevelZoneType, ClearedLevelZone);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReachedNewLevel);

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
	UPROPERTY(BlueprintAssignable, Category="Level Zone Subsystem Events")
	FOnReachedNewLevel OnReachedNewLevel;
	UPROPERTY(BlueprintAssignable, Category="Level Zone Subsystem Events")
	FOnClearedLevel OnClearedLevel;

	UFUNCTION(BlueprintCallable, Category= "LevelZone Subsystem Functions")
	void TriggerReachedNewLevel() const;
	UFUNCTION(BlueprintCallable, Category= "LevelZone Subsystem Functions")
	void TriggerClearedLevel() const;
	
private:
	
};
