// Fill out your copyright notice in the Description page of Project Settings.


#include "Patrol.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "Navigation/PathFollowingComponent.h"

UPatrol::UPatrol()
{
	NodeName = "Find Patrol Point";

	
}

EBTNodeResult::Type UPatrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* Pawn = OwnerComp.GetAIOwner()->GetPawn();


	
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

