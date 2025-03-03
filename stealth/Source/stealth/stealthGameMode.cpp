// Copyright Epic Games, Inc. All Rights Reserved.

#include "stealthGameMode.h"
#include "stealthCharacter.h"
#include "UObject/ConstructorHelpers.h"

AstealthGameMode::AstealthGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AstealthGameMode::NotifyEndGame(bool Success)
{
	if (IsEndGame) return;

	IsEndGame = true;

	OnEndGame.Broadcast(Success);
}
