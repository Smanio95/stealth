// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "FindRandomPoint.generated.h"

/**
 * 
 */
UCLASS()
class STEALTH_API UFindRandomPoint : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UFindRandomPoint();

protected:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditAnywhere)
	float Radius = 300;
	
};
