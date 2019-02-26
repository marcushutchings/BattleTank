// Corpyright Marcus Hutchings 2019

#include "SprungWheel.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Spring = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Spring Physics Constraint"));
	SetRootComponent(Spring);

	WheelMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel Mesh"));
	//WheelMesh->SetSimulatePhysics(true);
	WheelMesh->SetupAttachment(Spring);

	// Prevent any angular momentum
	Spring->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0.f);
	Spring->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0.f);
	Spring->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0.f);

	// Spring the wheel and body vertically
	Spring->SetLinearPositionDrive(false, false, true);
	Spring->SetLinearVelocityDrive(false, false, true);
	Spring->SetLinearDriveParams(50.f, 20.f, 0.f);

	// Allow the wheel to fall and rise separately.
	Spring->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0.f);
	Spring->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0.f);
	Spring->SetLinearZLimit(ELinearConstraintMotion::LCM_Free, 0.f);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	
	if (GetAttachParentActor())
	{
		auto TankBody = Cast<UStaticMeshComponent>(GetAttachParentActor()->GetRootComponent());
		Spring->SetConstrainedComponents(TankBody, NAME_None, WheelMesh, NAME_None);
	}
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

