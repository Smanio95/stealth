// Fill out your copyright notice in the Description page of Project Settings.


#include "FindEnemyPatrolPoints.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy.h"
#include "AIController.h"

UFindEnemyPatrolPoints::UFindEnemyPatrolPoints()
{
	NodeName = "Find Patrol Point";

	BlackboardKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UFindEnemyPatrolPoints, BlackboardKey));
}

EBTNodeResult::Type UFindEnemyPatrolPoints::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AEnemy* Enemy = Cast<AEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	int* Counter = reinterpret_cast<int*>(NodeMemory);

	FVector FinalLocation = Enemy->GetActorLocation();

	if (Enemy->PatrolPoints.Num() > 0)
	{
		*Counter = *Counter % Enemy->PatrolPoints.Num();

		AActor* PatrolPoint = Enemy->PatrolPoints[*Counter];
		FinalLocation = PatrolPoint->GetActorLocation();
	}

	OwnerComp.GetAIOwner()->GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName, FinalLocation);

	*Counter += 1;

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

uint16 UFindEnemyPatrolPoints::GetInstanceMemorySize() const
{
	return sizeof(int);
}
