// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class ATank;

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		float CrossHairXLocation = 0.5f;

	UPROPERTY(EditAnywhere)
		float CrossHairYLocation = (1.f / 3.f);

	UPROPERTY(EditAnywhere)
		float LineTraceRange = 1000000;

	ATank* GetControlledTank() const;

	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& OutLocationHitInWorldByRay) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
};
