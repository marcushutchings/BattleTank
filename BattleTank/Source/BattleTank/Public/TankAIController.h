// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

class ATank;
class UTankAimingComponent;

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
	ATank* GetControlledTank() const;

	ATank* GetPlayerTank() const;

	UPROPERTY(EditDefaultsOnly)
		float AcceptanceRadius = 3000.f;

	UTankAimingComponent* AimingComponent = nullptr;

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
};
