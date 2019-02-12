// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Public/TankBarrel.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTankAimingComponent::AimAt(FVector LocationToAimAt, float ProjectileSpeed)
{
	if (Barrel)
	{
		FVector SuggestedProjectileVelocity;

		bool result = UGameplayStatics::SuggestProjectileVelocity
		(
			this,
			SuggestedProjectileVelocity,
			Barrel->GetSocketLocation(FName("MuzzleEnd")),
			LocationToAimAt,
			ProjectileSpeed,
			false,
			0.f,
			0.f,
			ESuggestProjVelocityTraceOption::DoNotTrace
		);

		auto AimDirection = SuggestedProjectileVelocity.GetSafeNormal();

		MoveBarrel(AimDirection);

		//UE_LOG(LogTemp, Warning, TEXT("%s aiming direction is %s (%d)"), *GetOwner()->GetName(), *AimDirection.ToString(), result);
	}

	//UE_LOG(LogTemp, Warning, TEXT("%s has barrel %s"), *GetName(), *Barrel->Positi->GetName());
}

void UTankAimingComponent::SetBarrelMesh(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	FRotator BarrelRotation;

	auto CurrentBarrelRotation = Barrel->GetForwardVector().Rotation();
	auto TargetRotation = AimDirection.Rotation();

	auto DelatRotation = TargetRotation - CurrentBarrelRotation;

	Barrel->Elevate(1);

	UE_LOG(LogTemp, Warning, TEXT("Aim as %s"), *TargetRotation.ToString());
}

