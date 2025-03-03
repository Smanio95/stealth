// Fill out your copyright notice in the Description page of Project Settings.


#include "WinBox.h"
#include <stealth/stealthCharacter.h>
#include <stealth/stealthGameMode.h>

void UWinBox::BeginPlay()
{
	OnComponentBeginOverlap.AddUniqueDynamic(this, &UWinBox::OnBeginOverlap);
}

void UWinBox::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AstealthCharacter* Player = Cast<AstealthCharacter>(OtherActor);

	if (!Player) return;

	Player->CustomReposition(Player->GetActorTransform(), GetComponentTransform());

	AstealthGameMode* GM = Cast<AstealthGameMode>(GetWorld()->GetAuthGameMode());

	if (GM) GM->NotifyEndGame(true);
}
