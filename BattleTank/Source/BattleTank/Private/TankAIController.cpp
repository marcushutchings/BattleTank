// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"
#include "Engine/World.h"
#include "Public/Tank.h"
#include "Public/TankAimingComponent.h"


ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	APlayerController* playerController = GetWorld()->GetFirstPlayerController();
	if (playerController)
	{
		APawn* activePawn = playerController->GetPawn();
		if (activePawn)
		{
			return Cast<ATank>(activePawn);
		}
	}
	return nullptr;
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (ControlledTank)
	{
		AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	}
}

void ATankAIController::Tick(float DeltaSeconds)
{
	auto targetTank = GetPlayerTank();
	if (targetTank && ensure(AimingComponent))
	{
		MoveToActor(targetTank, AcceptanceRadius);
		AimingComponent->AimAt(targetTank->GetActorLocation());
		GetControlledTank()->Fire();
	}
}
