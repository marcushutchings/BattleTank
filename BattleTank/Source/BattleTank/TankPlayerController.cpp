// Copyright Marcus Hutchings 2019.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Public/Tank.h"
#include "Public/TankAimingComponent.h"

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
	auto ControlledTank = GetControlledTank();
	if (ControlledTank)
	{
		auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
		if (AimingComponent)
			FoundAimingComponent(AimingComponent);
		else
			UE_LOG(LogTemp, Error, TEXT("Tank Player Controller could not find Tank Aiming Component."));
	}
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AimTowardsCrosshair();
}
