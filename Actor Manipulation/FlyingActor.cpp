// Fill out your copyright notice in the Description page of Project Settings.


#include "FlyingActor.h"

// Sets default values
AFlyingActor::AFlyingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFlyingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFlyingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	//----
	//HAPPENS EVERY TICK. GAME LOOP

	//declares a var every frame that gets the actors current location, effectively changing the location.
	FVector ChangedLocation = GetActorLocation();
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));		//set delta height variable for smooth motion.
	//get each coord of the actor's location and add and assign DeltaTime * the Value. Can edit the values in editor. 
	ChangedLocation.X += DeltaHeight * XVal;
	ChangedLocation.Y += DeltaHeight * YVal;
	ChangedLocation.Z += DeltaHeight * ZVal;

	RunningTime += DeltaTime;					//set running time to deltatime
	SetActorLocation(ChangedLocation);			//Setting actors location to the new changed location.

	//USE 'Movement' CATEGORY IN EDITOR TO ADJUST HOW THE ACTOR FLYS.
	
	//-----
}

