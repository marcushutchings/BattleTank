// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankAIController.h"
#include "Engine/World.h"
#include "Public/Tank.h"
#include "Public/TankAimingComponent.h"


APawn * ATankAIController::GetPlayerTank() const
{
	APlayerController* playerController = GetWorld()->GetFirstPlayerController();
	if (playerController)
	{
		return playerController->GetPawn();
	}
	return nullptr;
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}

void ATankAIController::Tick(float DeltaSeconds)
{
	auto targetTank = GetPlayerTank();
	if (targetTank && ensure(AimingComponent))
	{
		MoveToActor(targetTank, AcceptanceRadius);
		AimingComponent->AimAt(targetTank->GetActorLocation());
		//UE_LOG(LogTemp, Warning, TEXT("Battel mode %d"), (uint8)AimingComponent->GetFiringStatus());
		if (AimingComponent->GetFiringStatus() == EFiringStatus::Locked)
			AimingComponent->Fire();
	}
}
