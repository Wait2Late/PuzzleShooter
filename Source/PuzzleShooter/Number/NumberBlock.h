// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "PuzzleShooter/Game Instance/NumbersGameInstance.h"
#include "NumberBlock.generated.h"

UCLASS()
class PUZZLESHOOTER_API ANumberBlock : public AActor/*, public IGameInstanceInterface*/
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ANumberBlock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category="Base")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere)
	UStaticMesh* CubeMeshRef;

	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxComponent;
	

public:
	// TArray<int> StoredNumbers;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "TextNumber Category")
	FString TextNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "TextNumber Category")
	int NumpadNumber;

	// UNumbersGameInstance NumbersGameInstance;

	// virtual void SetNumber_Implementation(int AddNumber) override;
	// virtual TArray<int> GetNumber_Implementation() override;
	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnOverlapBegin(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
		);


};
