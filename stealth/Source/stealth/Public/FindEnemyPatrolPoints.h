// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "FindEnemyPatrolPoints.generated.h"

/**
 * 
 */
UCLASS()
class STEALTH_API UFindEnemyPatrolPoints : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UFindEnemyPatrolPoints();

protected:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	uint16 GetInstanceMemorySize() const override;
	
};
