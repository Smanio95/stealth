// Fill out your copyright notice in the Description page of Project Settings.


#include "AlarmWidget.h"

void UAlarmWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UAlarmWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (PartialRateo == AlarmRateo)
	{
		AlarmTimer += GetWorld()->GetDeltaSeconds();

		if (AlarmTimer >= ThresholdBeforeUnalarm)
		{
			PartialRateo = 0;
			AlarmRateo = FMath::FInterpConstantTo(AlarmRateo, PartialRateo, GetWorld()->GetDeltaSeconds(), AlarmDecreaseSpeed);
		}
	}
	else 
	{
		AlarmRateo = FMath::FInterpConstantTo(AlarmRateo, PartialRateo, GetWorld()->GetDeltaSeconds(), AlarmIncreaseSpeed);
	}

	SetRenderOpacity(AlarmRateo);

	AlarmRateo = FMath::Clamp(AlarmRateo, 0, 1);
}

void UAlarmWidget::UpdateAlarm(float Multiplier, bool IsFullyAlarmed)
{
	if (Multiplier > 0)
	{
		AlarmTimer = 0;
		PartialRateo += AlarmIncreaseSpeed * Multiplier;
	}
	else
	{
		PartialRateo = 0;
	}

	PartialRateo = FMath::Clamp(PartialRateo, 0, 1);

	if (IsFullyAlarmed) PartialRateo = 1;

	if (PartialRateo == 1)
	{
		OnAlarmed.Broadcast();
	}
	else if (PartialRateo == 0)
	{
		OnUnAlarmed.Broadcast();
	}
}
