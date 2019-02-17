// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankTrack.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"

void UTankTrack::SetThrottle(float Throttle)
{
	auto ClampedThrottle = FMath::Clamp<float>(Throttle, 0.f, 1.f);
	UE_LOG(LogTemp, Warning, TEXT("Throttle set to %f: %f"), ClampedThrottle, GetWorld()->GetTimeSeconds());

	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForceNewtons;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

