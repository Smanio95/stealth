// Fill out your copyright notice in the Description page of Project Settings.


#include "ResetAlarm.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy.h"
#include "AIController.h"

UResetAlarm::UResetAlarm()
{
	NodeName = "Reset Alarm";

	BlackboardKey.AddBoolFilter(this, GET_MEMBER_NAME_CHECKED(UResetAlarm, BlackboardKey));
}

EBTNodeResult::Type UResetAlarm::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AEnemy* Enemy = Cast<AEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	Enemy->Deactivate(BlackboardKey.SelectedKeyName);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
