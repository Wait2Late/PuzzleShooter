﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "../PoolingSystem/PoolingActorBase.h"
#include "EnemyBase.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPoolingEnemyDespawn, APoolingActorBase*, PoolingActor);

UCLASS()
class PUZZLESHOOTER_API AEnemyBase : public APoolingActorBase
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// UFUNCTION(BlueprintCallable, Category="Pooled Actor Category")
	// virtual void Deactivate() override;
 
	// FOnPoolingEnemyDespawn OnPoolingEnemyDespawn;
};
