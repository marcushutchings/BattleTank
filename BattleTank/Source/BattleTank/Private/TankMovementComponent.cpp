// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankMovementComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Public/TankTrack.h"

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	auto ClampedThrow = FMath::Clamp(Throw, -1.f, 1.f);
	//UE_LOG(LogTemp, Warning, TEXT("Intend right %f: %f"), ClampedThrow, GetWorld()->GetTimeSeconds());

	auto ThrowLeft = ClampedThrow;
	auto ThrowRight = -ClampedThrow;

	if (LeftTrack && RightTrack)
	{
		LeftTrack->SetThrottle(ThrowLeft);
		RightTrack->SetThrottle(ThrowRight);
	}
}

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	UE_LOG(LogTemp, Warning, TEXT("Request Direct Move %s from %s"), *MoveVelocity.ToString(), *GetOwner()->GetName());
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	auto ClampedThrow = FMath::Clamp(Throw, -0.5f, 1.f);
	//UE_LOG(LogTemp, Warning, TEXT("Intend move %f: %f"), ClampedThrow, GetWorld()->GetTimeSeconds());

	if (LeftTrack && RightTrack)
	{
		LeftTrack->SetThrottle(ClampedThrow);
		RightTrack->SetThrottle(ClampedThrow);
	}
}

