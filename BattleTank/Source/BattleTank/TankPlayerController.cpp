// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (GetControlledTank())
	{
		FVector HitLocation;
		if (GetSightRayHitLocation(HitLocation))
		{
			UE_LOG(LogTemp, Warning, TEXT("Line trace hit location: %s"), *HitLocation.ToString());
		}
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & OutLocationHitInWorldByRay) const
{
	OutLocationHitInWorldByRay = FVector(0.f);
	return true;
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay!"));
	ATank* meep = GetControlledTank();
	if (meep){
		UE_LOG(LogTemp, Warning, TEXT("Tank, %s, Controlled!"), *meep->GetName());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No Tank Controlled!"));
	}
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AimTowardsCrosshair();
}
