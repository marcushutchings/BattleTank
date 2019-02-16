// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "../Public/TankAIController.h"
#include "Engine/World.h"
#include "Public/Tank.h"


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
	/*ATank* meep = GetControlledTank();
	if (meep) {
		UE_LOG(LogTemp, Warning, TEXT("Tank, %s, AI Controlled!"), *meep->GetName());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No Tank AI Controlled!"));
	}
	ATank* playeyTank = GetPlayerTank();
	if (playeyTank) {
		UE_LOG(LogTemp, Warning, TEXT("Found Player Tank, %s!"), *playeyTank->GetName());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Could not find player tank!"));
	}*/
}

void ATankAIController::Tick(float DeltaSeconds)
{
	auto targetTank = GetPlayerTank();
	if (targetTank)
	{
		GetControlledTank()->AimAt(targetTank->GetActorLocation());
		GetControlledTank()->Fire();
	}
}
