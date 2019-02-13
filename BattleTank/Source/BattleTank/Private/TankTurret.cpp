// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankTurret.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"

void UTankTurret::Pan(float RelativeSpeed)
{
	auto ClampedRelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);
	auto PanChange = ClampedRelativeSpeed * MaxDegressPerSecondRotation * GetWorld()->DeltaTimeSeconds;
	auto RawNewPan = RelativeRotation.Yaw + PanChange;

	SetRelativeRotation(FRotator(RelativeRotation.Pitch, RawNewPan, RelativeRotation.Roll));
}

