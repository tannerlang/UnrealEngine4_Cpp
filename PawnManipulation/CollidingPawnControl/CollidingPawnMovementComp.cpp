// creating a movement component for pawn


#include "CollidingPawnMovementComp.h"

//define
void UCollidingPawnMovementComp::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Check
	if (!PawnOwner || !UpdatedComponent || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	//gets movement vector in ACollidingPawn::Tick and clears it.
		//set max speed 150 UE u/s
	FVector MovementSpeed = ConsumeInputVector().GetClampedToMaxSize(1.0f) * DeltaTime * 150.0f;
	if (!MovementSpeed.IsNearlyZero())
	{
		FHitResult Hit;
		SafeMoveUpdatedComponent(MovementSpeed, UpdatedComponent->GetComponentRotation(), true, Hit);

		//if hit something, slide against it.
		if (Hit.IsValidBlockingHit())
		{
			SlideAlongSurface(MovementSpeed, 1.F - Hit.Time, Hit.Normal, Hit);
		}
	}
};


//above function uses important UPawnMovementComponent class members.
//ConsumeInputVector() reports and clears value of built in variable used to store movement inputs.
//SafeMoveUpdatedComponent uses UE physics to move PawnMovementComp and respects solids.
//SlideAlongSurface handles physics with sliding smoothly against collision surfaces.