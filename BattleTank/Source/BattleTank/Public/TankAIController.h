// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
	
	UTankAimingComponent* AimingComponent = nullptr;

	APawn* GetPlayerTank() const;

	UFUNCTION()
		void OnTankDeath();

protected:
	UPROPERTY(EditDefaultsOnly)
		float AcceptanceRadius = 3000.f;

public:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void SetPawn(APawn* InPawn) override;
};
