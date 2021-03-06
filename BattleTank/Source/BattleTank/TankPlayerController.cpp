// Copyright Marcus Hutchings 2019.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Public/Tank.h"
#include "Public/TankAimingComponent.h"


void ATankPlayerController::AimTowardsCrosshair()
{
	if (ensure(AimingComponent))
	{
		FVector HitLocation;
		if (GetSightRayHitLocation(HitLocation))
		{
			AimingComponent->AimAt(HitLocation);
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

	//UE_LOG(LogTemp, Warning, TEXT("Aim point is %s %d!"), *LookDirection.ToString(), result);
	//UE_LOG(LogTemp, Warning, TEXT("Aim point is %s %d!"), *HitLocation.ToString(), result);

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
		ECollisionChannel::ECC_Camera
	);

	if (result)
	{
		HitLocation = HitResult.Location;
	}

	return result;
}

void ATankPlayerController::OnTankDeath()
{
	controlsActive = false;
	StartSpectatingOnly();
	//UE_LOG(LogTemp, Warning, TEXT("Player Tank Died"));
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (GetPawn())
	{
		AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
		if (AimingComponent)
			FoundAimingComponent(AimingComponent);
		else
			UE_LOG(LogTemp, Error, TEXT("Tank Player Controller could not find Tank Aiming Component."));
	}
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (controlsActive)
		AimTowardsCrosshair();
}

void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto TankToPossess = Cast<ATank>(InPawn);
		if (TankToPossess)
		{
			controlsActive = true;
			TankToPossess->OnTankDeath.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);
		}
	}
}
