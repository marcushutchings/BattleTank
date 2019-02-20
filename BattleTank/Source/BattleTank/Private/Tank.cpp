// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Tank.h"
#include "Public/TankAimingComponent.h"
#include "Public/TankBarrel.h"
#include "Public/Projectile.h"
#include "Engine/World.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::AimAt(FVector Location)
{
	if (TankAimingComponent)
	{
		TankAimingComponent->AimAt(Location, LaunchProjectileSpeed);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("TankAiming Component is missing on %s"), *GetOwner()->GetName());
	}
}

void ATank::Fire()
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

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	//PrimaryActorTick.bCanEverTick = false;

	TankAimingComponent = FindComponentByClass<UTankAimingComponent>();
	Barrel = FindComponentByClass<UTankBarrel>();
}


