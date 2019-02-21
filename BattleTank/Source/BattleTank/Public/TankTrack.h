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

public:
	UTankTrack();
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "Input")
		void SetThrottle(float Throttle);
	
protected:
	UPROPERTY(EditDefaultsOnly)
		float TrackMaxDrivingForceNewtons = 30000000.f; // 40,000kg * 10m/s (1g) [10000]

	// Called when the game starts
	virtual void BeginPlay() override;

private:
	void CorrectTrackSideWaysVelocity(float DeltaTime);
};
