// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Investigate.generated.h"

/**
 * 
 */
UCLASS()
class STEALTH_API UInvestigate : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

protected:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
