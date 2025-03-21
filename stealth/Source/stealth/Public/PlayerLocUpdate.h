// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "PlayerLocUpdate.generated.h"

/**
 * 
 */
UCLASS()
class STEALTH_API UPlayerLocUpdate : public UBTService_BlackboardBase
{
	GENERATED_BODY()

protected:
	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
