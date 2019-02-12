// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Public/Tank.h"

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
			GetControlledTank()->AimAt(HitLocation);
			//UE_LOG(LogTemp, Warning, TEXT("Line trace hit location: %s"), *HitLocation.ToString());
		}
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector & HitLocation) const
{
	bool result;

	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	float locationX = ViewportSizeX * CrossHairXLocation;
	float locationY = ViewportSizeY * CrossHairYLocation;
	FVector2D ScreenLocation = FVector2D(locationX, locationY);

	FVector LookDirection;
	result = GetLookDirection(ScreenLocation, LookDirection);
	if (result)
	{
		result = GetLookVectorHitLocation(LookDirection, HitLocation);
	}

	//UE_LOG(LogTemp, Warning, TEXT("Aim point is %s!"), *LookDirection.ToString());
	//UE_LOG(LogTemp, Warning, TEXT("Aim point is %s!"), *ScreenLocation.ToString());

	return result;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraLocation;

	return DeprojectScreenPositionToWorld
	(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraLocation,
		LookDirection
	);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FVector StartPoint, EndPoint;
	FHitResult HitResult;

	StartPoint = PlayerCameraManager->GetCameraLocation();
	EndPoint = StartPoint + LookDirection*LineTraceRange;

	bool result = GetWorld()->LineTraceSingleByChannel
	(
		HitResult,
		StartPoint,
		EndPoint,
		ECollisionChannel::ECC_Visibility
	);

	if (result)
	{
		HitLocation = HitResult.Location;
	}

	return result;
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
