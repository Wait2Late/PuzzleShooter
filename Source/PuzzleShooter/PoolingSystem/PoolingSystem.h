// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PoolingActorBase.h"
#include "GameFramework/Actor.h"
#include "PoolingSystem.generated.h"

UCLASS()
class PUZZLESHOOTER_API APoolingSystem : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APoolingSystem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Functions
	UFUNCTION(BlueprintCallable, Category="Pooling Category")
	int GetPoolSize();

	UFUNCTION(BlueprintCallable, Category = "Pooling Category")
	APoolingActorBase* SpawnActor(FVector SpawnTransform);

	UFUNCTION(BlueprintCallable, Category = "Pooling Category")
	APoolingActorBase* OnBeginPool();

	UFUNCTION()
	void OnPoolingActorDespawn(APoolingActorBase* PoolingActor);

	//Variables
	UPROPERTY(BlueprintReadWrite, Category = "Pooling Category")
	TArray<APoolingActorBase*> PoolingActors;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pooling Category")
	TSubclassOf<APoolingActorBase> PoolingActor;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pooling Category")
	int PoolSize = 20;

	UPROPERTY(EditAnywhere, Category = "Pooling Category")
	float PooledLifeSpan = 0.0f;
	
	

protected:
	const FVector PoolLocation = FVector(0.0f, 0.0f, 10000.0f);

	TArray<int32> SpawnedActorIndex;

	
};
