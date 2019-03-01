// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankTrack.h"
#include "Engine/World.h"
#include "Math/UnrealMathUtility.h"
#include "Public/SprungWheel.h"
#include "Public/SpawnPoint.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//CorrectTrackSideWaysVelocity(DeltaTime);
}

void UTankTrack::SetThrottle(float Throttle)
{
	//CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -0.7f, 1.f);
	DriveTrack(FMath::Clamp<float>(Throttle, -0.7f, 1.f));
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	//auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForceNewtons;
	//auto ForceLocation = GetComponentLocation();
	//auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	//TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

	auto Wheels = GetWheels();
	auto ForceMagnitude = CurrentThrottle * TrackMaxDrivingForceNewtons;
	float ForcePerWheel = 0.f;

	if (Wheels.Num() > 0)
		ForcePerWheel = ForceMagnitude / Wheels.Num();

	for (auto Wheel : Wheels)
	{
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	//OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}
/*
void UTankTrack::CorrectTrackSideWaysVelocity()
{
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectionAcceleration = (-SlippageSpeed / DeltaTime) * GetRightVector();
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	if (ensure(TankRoot))
	{
		auto CorrectionForce = TankRoot->GetMass() * CorrectionAcceleration *0.5f;
		TankRoot->AddForce(CorrectionForce);
	}
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	DriveTrack();
	CorrectTrackSideWaysVelocity();
	CurrentThrottle = 0.f;
	//UE_LOG(LogTemp, Warning, TEXT("I'm hit, I'm hit"))
}
*/
TArray<class ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<ASprungWheel*> ListOfWheels;
	TArray<USceneComponent*> ListOfSubComponents;

	GetChildrenComponents(false, ListOfSubComponents);
	for (auto SubComponent : ListOfSubComponents)
	{
		auto SpawnPoint = Cast<USpawnPoint>(SubComponent);
		if (SpawnPoint)
		{
			auto SpawnedComponent = SpawnPoint->GetSpawnedActor();
			auto Wheel = Cast<ASprungWheel>(SpawnedComponent);
			if (Wheel)
			{
				ListOfWheels.Add(Wheel);
			}
		}
	}
	return ListOfWheels;
}

