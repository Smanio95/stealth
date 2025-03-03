// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "WinBox.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class STEALTH_API UWinBox : public UBoxComponent
{
	GENERATED_BODY()

protected:
	void BeginPlay() override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
