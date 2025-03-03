// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndGamePanel.generated.h"

/**
 * 
 */
UCLASS()
class STEALTH_API UEndGamePanel : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString WinTxt = "YOU WON";

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString LoseTxt = "YOU LOST";

	UFUNCTION(BlueprintImplementableEvent)
	void OnEndGame(bool Success);

	UFUNCTION(BlueprintCallable)
	void Retry();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString LevelToOpen;

	UFUNCTION(BlueprintCallable)
	void Quit();

	void NativeConstruct() override;
};
