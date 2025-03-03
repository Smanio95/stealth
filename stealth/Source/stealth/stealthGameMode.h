// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "stealthGameMode.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEndGame, bool, Success);

UCLASS(minimalapi)
class AstealthGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AstealthGameMode();

protected:
	bool IsEndGame = false;

public:
	void NotifyEndGame(bool Success);

	UPROPERTY(BlueprintAssignable)
	FOnEndGame OnEndGame;
};



