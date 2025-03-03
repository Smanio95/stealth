// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AlarmWidget.h"
#include <Components/WidgetComponent.h>
#include <AIController.h>
#include "BehaviorTree/BlackboardComponent.h"
#include "BrainComponent.h"
#include <Kismet/KismetSystemLibrary.h>
#include <stealth/stealthCharacter.h>
#include <Kismet/GameplayStatics.h>
#include <stealth/stealthGameMode.h>
#include <Kismet/KismetMathLibrary.h>

// Sets default values
AEnemy::AEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* Widget = GetComponentByClass<UWidgetComponent>()->GetWidget();
	Alarm = Cast<UAlarmWidget>(Widget);

	if (Alarm)
	{
		Alarm->OnAlarmed.AddUniqueDynamic(this, &AEnemy::OnAlarmed);
		Alarm->OnUnAlarmed.AddUniqueDynamic(this, &AEnemy::OnUnAlarmed);
	}

	GetCharacterMovement()->MaxWalkSpeed = PatrolMovSpeed;
}

void AEnemy::OnAlarmed()
{
	if (bIsAlarmed) return;

	bIsAlarmed = true;

	GetCharacterMovement()->MaxWalkSpeed = ChaseMovSpeed;

	UpdateAlarm();

	UpdateWhereToGo();
}

void AEnemy::OnUnAlarmed()
{
	if (!bIsAlarmed) return;

	bIsAlarmed = false;

	GetCharacterMovement()->MaxWalkSpeed = PatrolMovSpeed;

	UpdateAlarm();
}

void AEnemy::UpdateAlarm()
{
	UpdateAlarm("Alarmed");
}

void AEnemy::UpdateAlarm(FName BlackboardKey)
{
	AAIController* AIController = Cast<AAIController>(GetController());

	if (!AIController) return;

	UBlackboardComponent* BB = AIController->GetBlackboardComponent();
	BB->SetValueAsBool(BlackboardKey, bIsAlarmed);
}

void AEnemy::UpdateWhereToGo()
{
	AAIController* AIController = Cast<AAIController>(GetController());

	if (!AIController) return;

	UBlackboardComponent* BB = AIController->GetBlackboardComponent();
	BB->SetValueAsVector("WhereToGo", UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetActorLocation());
}

void AEnemy::OnSeePlayer()
{
	Alarm->UpdateAlarm(1.f, true);

	if (bIsAlarmed) UpdateWhereToGo();
}

void AEnemy::OnHearPlayer(float Volume)
{
	if (bIsAlarmed) return;

	Alarm->UpdateAlarm(Volume, false);
}

void AEnemy::Immobilize()
{
	GetCharacterMovement()->SetActive(false);

	SetActorEnableCollision(false);

	if (Alarm)
	{
		UWidgetComponent* Widget = GetComponentByClass<UWidgetComponent>();
		Widget->SetVisibility(false);
	}

	// stop brain logic
	AAIController* AIController = Cast<AAIController>(GetController());

	if (!AIController) return;

	AIController->GetBrainComponent()->StopLogic(FString());
}

void AEnemy::OnEndGame(bool Success)
{
	if (!Success) return;

	Immobilize();
}

bool AEnemy::HasCatchedPlayer(FVector LookAtPos)
{
	//SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), FVector(LookAtPos.X, LookAtPos.Y, GetActorLocation().Z)));

	FVector Dir = FVector(LookAtPos.X, LookAtPos.Y, GetActorLocation().Z) - GetActorLocation();
	Dir.Normalize();

	AddMovementInput(Dir, 100);

	EObjectTypeQuery PlayerType = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn);
	TArray<AActor*> Out;

	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), GetActorLocation(), CatchSphereRadius, { PlayerType }, AstealthCharacter::StaticClass(), { this }, Out);

	return Out.Num() > 0;
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy::ToggleFocus(bool Active)
{
	GetMesh()->SetOverlayMaterial(Active ? FocusedM : nullptr);
}

void AEnemy::Deactivate(FName BlackboardKey)
{
	IsInvestigating = true;

	Alarm->UpdateAlarm(0, false);
}

void AEnemy::Die()
{
	IsDead = true;

	ToggleFocus(false);
}

void AEnemy::EndGame()
{
	UAnimInstance* Instance = GetMesh()->GetAnimInstance();

	Instance->OnMontageStarted.AddUniqueDynamic(this, &AEnemy::OnAnimStart);

	float MLength = Instance->Montage_Play(AttackMontage);

	// stop brain logic
	AAIController* AIController = Cast<AAIController>(GetController());

	if (!AIController) return;

	AIController->GetBrainComponent()->StopLogic(FString());
}

void AEnemy::OnAnimStart(UAnimMontage* Montage)
{
	AstealthGameMode* GM = Cast<AstealthGameMode>(GetWorld()->GetAuthGameMode());

	if (GM) GM->NotifyEndGame(false);
}

