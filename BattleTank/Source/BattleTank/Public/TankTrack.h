// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingForceNewtons = 40000000.f; // 40,000kg * 10m/s (1g) [10000]
	
public:

	UFUNCTION(BlueprintCallable, Category = "Input")
		void SetThrottle(float Throttle);
	
	
};
