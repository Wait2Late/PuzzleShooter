// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_FindRandomLocation.h"

#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PuzzleShooter/Enemy/EnemyController.h"

UBTTask_FindRandomLocation::UBTTask_FindRandomLocation(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Find Random Location in NavMesh";
}

EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	if (TObjectPtr<AEnemyController> const Controller = Cast<AEnemyController>(OwnerComp.GetAIOwner()))
	{
		if (auto const Enemy = Controller->GetPawn())
		{
			auto const Origin = Enemy->GetActorLocation();

			if (auto const NavSys = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				FNavLocation NavLocation;
				if(NavSys->GetRandomPointInNavigableRadius(Origin, SearchRadius, NavLocation))
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), NavLocation.Location);
				}

				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				
				return EBTNodeResult::Succeeded;
			}
		}
	}

	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
