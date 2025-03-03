// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Patrol.generated.h"

/**
 * 
 */
UCLASS()
class STEALTH_API UPatrol : public UBTTaskNode
{
	GENERATED_BODY()

	UPatrol();

protected:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	FName BlackboardKey;
	
};
