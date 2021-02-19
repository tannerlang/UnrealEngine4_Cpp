// creating a movement component for pawn

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "CollidingPawnMovementComp.generated.h"

/**
 * 
 */
UCLASS()
class CPPWORLD_API UCollidingPawnMovementComp : public UPawnMovementComponent
{
	GENERATED_BODY()
	
public:

	//tick component function declaration override - how the pawn moves each frame 
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
