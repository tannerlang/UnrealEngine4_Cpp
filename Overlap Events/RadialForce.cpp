// Fill out your copyright notice in the Description page of Project Settings.
//radial force can be used for the force of a grenade, bomb, ability, etc... in a game.

#include "RadialForce.h"
#include "DrawDebugHelpers.h"

// Sets default values
ARadialForce::ARadialForce()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARadialForce::BeginPlay()
{
	Super::BeginPlay();

	//creating tarray to collect all hit results in the range.
	TArray<FHitResult> OutHits;

	//gets actor locations
	FVector MyLocation = GetActorLocation();

	//start and end locations
	FVector Start = MyLocation;
	FVector End = MyLocation;

	//create collision sphere of 500 units. This is the radial sweep.
	FCollisionShape MyCollisionSphere = FCollisionShape::MakeSphere(500.f);

	//visualize the sphere with drawdebugsphere. passes the world, the center of the sphere, the radius, the #of segments, color, and a bool persistant lines.
	DrawDebugSphere(GetWorld(), GetActorLocation(), MyCollisionSphere.GetSphereRadius(), 50, FColor::Blue, true);

	//checks if anything got hit in sweep with SweepMultiByChannel().
	bool isHit = GetWorld()->SweepMultiByChannel(OutHits, Start, End, FQuat::Identity, ECC_WorldStatic, MyCollisionSphere);

	if (isHit)
	{
		//tArray loop. if hit is true, loop throught outhits tarray and add radial impulse to successfully casted actor's root components. 
		for (auto& Hit : OutHits)
		{
			UStaticMeshComponent* MeshComp = Cast<UStaticMeshComponent>((Hit.GetActor())->GetRootComponent());

			if (MeshComp)
			{
				MeshComp->AddRadialImpulse(GetActorLocation(), 500.f, 2000.f, ERadialImpulseFalloff::RIF_Constant, true);
			}
		}
	}

	Destroy();
}

// Called every frame
void ARadialForce::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

