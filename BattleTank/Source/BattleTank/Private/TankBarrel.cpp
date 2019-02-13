// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankBarrel.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	auto ClampedRelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);
	auto ElevationChange = ClampedRelativeSpeed * MaxDegressPerSecondRotation * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;

	float ClampedElevation = FMath::Clamp<float>(RawNewElevation, MinElevationInDegress, MaxElevationInDegress);

	SetRelativeRotation(FRotator(ClampedElevation, RelativeRotation.Yaw, RelativeRotation.Roll));
}


