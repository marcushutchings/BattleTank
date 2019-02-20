// Copyright Marcus Hutchings 2019.

#pragma once

class UTankAimingComponent;

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

	UPROPERTY(EditDefaultsOnly)
		float CrossHairXLocation = 0.5f;

	UPROPERTY(EditDefaultsOnly)
		float CrossHairYLocation = (1.f / 3.f);

	UPROPERTY(EditDefaultsOnly)
		float LineTraceRange = 1000000;

	UTankAimingComponent* AimingComponent = nullptr;

	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& OutLocationHitInWorldByRay) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

protected:

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
		void FoundAimingComponent(UTankAimingComponent* AimingCompRef);

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
};
