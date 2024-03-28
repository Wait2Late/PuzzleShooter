// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
UENUM(BlueprintType, Blueprintable)
enum class EEnemyType : uint8
{
	None,
	MeleeEnemy,
	RangedEnemy
};
