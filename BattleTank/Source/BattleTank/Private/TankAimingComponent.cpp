// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Public/TankBarrel.h"
#include "Public/TankTurret.h"
#include "Public/Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


void UTankAimingComponent::Fire()
{
	bool IsReadyToFire = (FPlatformTime::Seconds() - LastFiredTimeInSeconds) > ReloadTimeInSeconds;

	//UE_LOG(LogTemp, Warning, TEXT("BANG %f - %f > %f"), FPlatformTime::Seconds(), LastFiredTimeInSeconds, ReloadTimeInSeconds);

	if (Barrel && IsReadyToFire)
	{
		FVector Location = Barrel->GetSocketLocation(FName("MuzzleEnd"));
		FRotator Rotation = Barrel->GetSocketRotation(FName("MuzzleEnd"));
		AProjectile *NewProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Location, Rotation);
		if (NewProjectile)
		{
			NewProjectile->LaunchProjectile(LaunchProjectileSpeed);
			LastFiredTimeInSeconds = FPlatformTime::Seconds();
			//UE_LOG(LogTemp, Warning, TEXT("BANG %s -> %s"), *Rotation.ToString(), *NewProjectile->GetActorRotation().ToString());
		}
	}
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	PrimaryComponentTick.bCanEverTick = false;

	Barrel = GetOwner()->FindComponentByClass<UTankBarrel>();
	Turret = GetOwner()->FindComponentByClass<UTankTurret>();
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTankAimingComponent::AimAt(FVector LocationToAimAt)
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
			LaunchProjectileSpeed,
			false,
			0.f,
			0.f,
			ESuggestProjVelocityTraceOption::DoNotTrace
		);

		auto AimDirection = SuggestedProjectileVelocity.GetSafeNormal();

		MoveBarrel(AimDirection);

		if (Turret)
			MoveTurret(AimDirection);

		//UE_LOG(LogTemp, Warning, TEXT("%s aiming direction is %s (%d)"), *GetOwner()->GetName(), *AimDirection.ToString(), result);
	}

	//UE_LOG(LogTemp, Warning, TEXT("%s has barrel %s"), *GetName(), *Barrel->Positi->GetName());
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
	FRotator BarrelRotation;

	auto CurrentBarrelRotation = Barrel->GetForwardVector().Rotation();
	auto TargetRotation = AimDirection.Rotation();
	auto DelaRotation = TargetRotation - CurrentBarrelRotation;

	Barrel->Elevate(DelaRotation.Pitch);
}

void UTankAimingComponent::MoveTurret(FVector AimDirection)
{
	FRotator TurretRotation;

	auto CurrentTurretRotation = Turret->GetForwardVector().Rotation();
	auto TargetRotation = AimDirection.Rotation();
	auto DelaRotation = TargetRotation - CurrentTurretRotation;

	Turret->Pan(DelaRotation.Yaw);
}

