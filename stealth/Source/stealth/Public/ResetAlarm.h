// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "ResetAlarm.generated.h"

/**
 * 
 */
UCLASS()
class STEALTH_API UResetAlarm : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UResetAlarm();

protected:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
