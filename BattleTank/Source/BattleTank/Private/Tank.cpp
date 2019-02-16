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
	PrimaryActorTick.bCanEverTick = true;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

}

void ATank::AimAt(FVector Location)
{
	TankAimingComponent->AimAt(Location, LaunchProjectileSpeed);
}

void ATank::SetBarrelMesh(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
	TankAimingComponent->SetBarrelMesh(BarrelToSet);
}

void ATank::SetTurretMesh(UTankTurret * TurretToSet)
{
	TankAimingComponent->SetTurretMesh(TurretToSet);
}

void ATank::Fire()
{
	if (Barrel)
	{
		FVector Location = Barrel->GetSocketLocation(FName("MuzzleEnd"));
		FRotator Rotation = Barrel->GetSocketRotation(FName("MuzzleEnd"));
		AProjectile *NewProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Location, Rotation);
		if (NewProjectile)
			NewProjectile->LaunchProjectile(LaunchProjectileSpeed);
		UE_LOG(LogTemp, Warning, TEXT("BANG %s -> %s"), *Rotation.ToString(), *NewProjectile->GetActorRotation().ToString());
	}
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
	PrimaryActorTick.bCanEverTick = false;
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

