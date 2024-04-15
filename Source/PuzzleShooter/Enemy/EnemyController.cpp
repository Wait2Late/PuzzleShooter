// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyController.h"

#include "EnemyBase.h"


// Sets default values
AEnemyController::AEnemyController(FObjectInitializer const& ObjectInitializer)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (TObjectPtr<AEnemyBase> const EnemyBase = Cast<AEnemyBase>(InPawn))
	{
		if (TObjectPtr<UBehaviorTree> const Tree = EnemyBase->GetBehaviourTree())
		{
			UBlackboardComponent* BlackboardComponent;
			UseBlackboard(Tree->BlackboardAsset, BlackboardComponent);
			Blackboard = BlackboardComponent;
			RunBehaviorTree(Tree);
		}
	}
}

