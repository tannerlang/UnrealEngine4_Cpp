//Colliding Pawn



#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CollidingPawn.generated.h"

UCLASS()
class CPPWORLD_API ACollidingPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACollidingPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InInputComponent) override;


	//var to keep track of a particle system component
	UPROPERTY()
	class UParticleSystemComponent* MyParticleSystem;

	//var for collidingpawnmovementcomp
	UPROPERTY()
	class UCollidingPawnMovementComp* MovementComp;

	//override the pawn GetMovementComponent to return the custom pawn movement component.
	virtual  UPawnMovementComponent* GetMovementComponent() const override;

	//declare movement/input functions for pawn

	void MoveForward(float AxisVal);
	void MoveRight(float AxisVal);
	void Turn(float AxisVal);
	void ToggleParticles();

};
