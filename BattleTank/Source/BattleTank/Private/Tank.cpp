// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Tank.h"
#include "Math/UnrealMathUtility.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	//PrimaryActorTick.bCanEverTick = false;
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	float DamageToApply = FMath::Clamp(DamageAmount, 0.f, TankDamageCapacity);
	if (TankDamageCapacity > 0.f)
	{
		TankDamageCapacity -= DamageAmount;
		if (TankDamageCapacity <= 0.f)
			UE_LOG(LogTemp, Warning, TEXT("Tank is DEAD"));
	}
	return DamageToApply;
}
