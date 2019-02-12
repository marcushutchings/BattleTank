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

	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxDegressPerSecondRotation = 20.f;

	UPROPERTY(EditAnywhere, Category = Setup)
		float MaxElevationInDegress = 40.f;

	UPROPERTY(EditAnywhere, Category = Setup)
		float MinElevationInDegress = 0.f;
	
public:
	void Elevate(float DegreesPerSecond);
	
};
