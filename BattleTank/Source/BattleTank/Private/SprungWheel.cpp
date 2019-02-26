// Corpyright Marcus Hutchings 2019

#include "SprungWheel.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Body Mesh"));
	SetRootComponent(BodyMesh);

	WheelMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel Mesh"));
	WheelMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	Spring = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Spring Physics Constraint"));
	Spring->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	Spring->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0.f);
	Spring->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0.f);
	Spring->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0.f);
	Spring->SetLinearPositionDrive(false, false, true);
	Spring->SetLinearVelocityDrive(false, false, true);

}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

