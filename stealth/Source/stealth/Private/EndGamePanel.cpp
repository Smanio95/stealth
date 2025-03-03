// Fill out your copyright notice in the Description page of Project Settings.


#include "EndGamePanel.h"
#include <stealth/stealthGameMode.h>
#include <Kismet/KismetSystemLibrary.h>
#include <Kismet/GameplayStatics.h>

void UEndGamePanel::NativeConstruct()
{
	Super::NativeConstruct();

	AstealthGameMode* GM = Cast<AstealthGameMode>(GetWorld()->GetAuthGameMode());

	if (!GM) return;

	GM->OnEndGame.AddUniqueDynamic(this, &UEndGamePanel::OnEndGame);
}

void UEndGamePanel::Retry()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(LevelToOpen));
}

void UEndGamePanel::Quit()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}