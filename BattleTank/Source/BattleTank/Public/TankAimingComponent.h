// Copyright Marcus Hutchings 2019.

#pragma once

class AProjectile;
class UTankBarrel;
class UTankTurret;

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringStatus : uint8
{
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchProjectileSpeed = 10000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		double ReloadTimeInSeconds = 3.f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		int32 CurrentAmmunition = 10;

	UPROPERTY(BlueprintReadOnly, Category = "State")
		EFiringStatus FiringStatus = EFiringStatus::Reloading;


	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AimAt(FVector Location);

	UFUNCTION(BlueprintCallable, Category = "Action")
		void Fire();

	UFUNCTION(BlueprintCallable, Category = "State")
		int32 GetCurrentAmmunition() const;

	UFUNCTION(BlueprintCallable, Category = "State")
		EFiringStatus GetFiringStatus() const;

private:
	float LastFiredTimeInSeconds = 0.f;

	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	FVector AimDirection;

	void MoveBarrel(FVector AimDirection);
	void MoveTurret(FVector AimDirection);

	bool IsBarrelMoving();
	bool CanFire();
};
