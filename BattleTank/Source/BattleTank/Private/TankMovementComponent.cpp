// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankMovementComponent.h"
#include "Math/UnrealMathUtility.h"

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	auto ClampedThrow = FMath::Clamp(Throw, -0.5f, 1.f);
	UE_LOG(LogTemp, Warning, TEXT("Intend move %f: %f"), ClampedThrow, GetWorld()->GetTimeSeconds());
}

