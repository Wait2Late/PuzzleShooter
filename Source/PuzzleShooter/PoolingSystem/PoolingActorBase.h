// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PoolingActorBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPoolingActorDespawn, APoolingActorBase*, PoolingActor);


UCLASS()
class PUZZLESHOOTER_API APoolingActorBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APoolingActorBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	
	FOnPoolingActorDespawn OnPoolingActorDespawn;

	UFUNCTION(BlueprintCallable, Category="Pooled Actor Category")
	void Deactivate();

	UFUNCTION(BlueprintCallable, Category="Pooled Actor Category")
	void SetActive(bool IsActive);
	void SetLifeSpan(float LifeTime);
	void SetPoolIndex(int Index);
	int GetPoolIndex();

	UFUNCTION(BlueprintImplementableEvent)
	void OnSetActiveCalled(bool IsActive);

	bool IsActive() const;

protected:
		bool bIsActive;
    	float LifeSpan = 0.0f;
    	int32 PoolIndex; // = -1;
private:
	TObjectPtr<UPawnMovementComponent> MovementComponent;
	
};
