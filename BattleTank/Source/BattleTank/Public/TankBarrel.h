// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS( meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxDegressPerSecondRotation = 5.f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxElevationInDegress = 40.f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MinElevationInDegress = 0.f;
	
public:
	void Elevate(float RelativeSpeed);
	
};
