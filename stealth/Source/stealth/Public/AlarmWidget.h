// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AlarmWidget.generated.h"

struct FGeometry;

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAlarmed);

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUnAlarmed);

/**
 *
 */
UCLASS(Blueprintable)
class STEALTH_API UAlarmWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	void NativeConstruct() override;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AlarmIncreaseSpeed = .5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AlarmDecreaseSpeed = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ThresholdBeforeUnalarm = 2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float AlarmRateo = 0;

	float PartialRateo = 0;

	float AlarmTimer = 0;

public:
	UPROPERTY(BlueprintAssignable)
	FOnAlarmed OnAlarmed;

	UPROPERTY(BlueprintAssignable)
	FOnAlarmed OnUnAlarmed;

	UFUNCTION(BlueprintCallable)
	void UpdateAlarm(float Multiplier = 1, bool IsFullyAlarmed = false);

private:
	bool bIsAlarmed = false;

};
