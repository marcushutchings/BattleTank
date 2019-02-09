// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
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
