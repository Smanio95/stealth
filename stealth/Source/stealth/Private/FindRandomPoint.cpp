// Fill out your copyright notice in the Description page of Project Settings.


#include "FindRandomPoint.h"
#include <NavigationSystem.h>
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UFindRandomPoint::UFindRandomPoint()
{
	NodeName = "Find Random Point";

	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UFindRandomPoint, BlackboardKey));
}

EBTNodeResult::Type UFindRandomPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());

	if (NavSystem)
	{
		FNavLocation NavLoc;
		FVector FinalLoc = OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();

		if (NavSystem->GetRandomReachablePointInRadius(FinalLoc, Radius, NavLoc))
		{
			FinalLoc = NavLoc.Location;
		}

		OwnerComp.GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, FinalLoc);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}


