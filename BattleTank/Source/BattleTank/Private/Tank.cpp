// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Tank.h"
#include "TankAimingComponent.h"

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
	TankAimingComponent->SetBarrelMesh(BarrelToSet);
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

