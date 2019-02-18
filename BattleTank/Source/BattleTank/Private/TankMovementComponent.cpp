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
	//auto MoveWithoutZVal = MoveVelocity;
	//MoveWithoutZVal.Z = 0.f;

	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto ForwardIntention = MoveVelocity.GetSafeNormal();

	auto ForwardThrow = FVector::DotProduct(TankForward, ForwardIntention);
	IntendMoveForward(ForwardThrow);

	auto RightIntention = FVector::CrossProduct(TankForward, ForwardIntention).Z;
	IntendTurnRight(RightIntention);
	//UE_LOG(LogTemp, Warning, TEXT("Request Direct Move %s:%s from %s"), *TankForward.ToString(), *ForwardIntention.ToString(), *GetOwner()->GetName());
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

