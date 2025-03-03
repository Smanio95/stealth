// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class STEALTH_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Life")
	bool IsDead;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Behaviour")
	bool IsInvestigating;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Focus")
	UMaterialInstance* FocusedM;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Chase")
	bool bIsAlarmed = false;

	class UAlarmWidget* Alarm;

	UFUNCTION()
	void OnAlarmed();
	
	UFUNCTION()
	void OnUnAlarmed();

	void UpdateAlarm();

	void UpdateWhereToGo();

	UFUNCTION(BlueprintCallable, meta = (BlueprintProtected))
	void OnSeePlayer();

	UFUNCTION(BlueprintCallable, meta = (BlueprintProtected))
	void OnHearPlayer(float Volume);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Chase")
	float CatchSphereRadius = 100;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Chase")
	UAnimMontage* AttackMontage;


	UFUNCTION()
	void OnEndGame(bool Success);

public:	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Patrol")
	TArray<AActor*> PatrolPoints;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float PatrolMovSpeed = 300;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
	float ChaseMovSpeed = 550;

	UFUNCTION(BlueprintCallable)
	bool HasCatchedPlayer(FVector LookAtPos);

	void UpdateAlarm(FName BlackboardKey);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ToggleFocus(bool Active);

	void Deactivate(FName BlackboardKey);

	void Immobilize();

	void Die();

	// single enemy end game to be broadcasted through Gamemode
	void EndGame();

private:
	UFUNCTION()
	void OnAnimStart(UAnimMontage* Montage);

};
