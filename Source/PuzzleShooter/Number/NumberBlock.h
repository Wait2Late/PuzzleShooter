// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "PuzzleShooter/Enum/LevelZoneType.h"
#include "PuzzleShooter/Enum/NumpadType.h"
#include "NumberBlock.generated.h"

UCLASS()
class PUZZLESHOOTER_API ANumberBlock : public AActor
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "TextNumber Category")
	TEnumAsByte<ENumpadType> NumpadType;


	
	
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateNumberUI();

	UFUNCTION(BlueprintCallable)
	void C_Erasure();
	
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

	UFUNCTION(BlueprintCallable)
	void SetLevelZone(ELevelZoneType NewLevelZone);
	
private:
	UFUNCTION()
	void OnInitializeLevelZone(); //Not needed

protected:
	UPROPERTY(BlueprintReadOnly, Category= "TextNumber Category")
	TEnumAsByte<ELevelZoneType> LevelZone;

};
