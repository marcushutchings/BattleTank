// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankTrack.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	CorrectTrackSideWaysVelocity(DeltaTime);
}

void UTankTrack::SetThrottle(float Throttle)
{
	auto ClampedThrottle = FMath::Clamp<float>(Throttle, 0.f, 1.f);
	//UE_LOG(LogTemp, Warning, TEXT("Throttle set to %f: %f"), ClampedThrottle, GetWorld()->GetTimeSeconds());

	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForceNewtons;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
}

void UTankTrack::CorrectTrackSideWaysVelocity(float DeltaTime)
{
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto CorrectionAcceleration = (-SlippageSpeed / DeltaTime) * GetRightVector();
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	if (ensure(TankRoot))
	{
		auto CorrectionForce = TankRoot->GetMass() * CorrectionAcceleration *0.5f;
		TankRoot->AddForce(CorrectionForce);
	}
}

