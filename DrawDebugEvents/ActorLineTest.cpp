// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorLineTest.h"
#include "DrawDebugHelpers.h"

// Sets default values
AActorLineTest::AActorLineTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creating mesh components
	Mesh1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh One"));
	RootComponent = Mesh1;

	Mesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Two"));
	Mesh2->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AActorLineTest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActorLineTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Create an fhit result variable so I can track what it's hitting.
	FHitResult OutHit;

	//Get starting location for where the line will start. Starting it at the actor's location, then adjusting its location a little bit with Start.Z/X operations.
	FVector Start = GetActorLocation();

	Start.Z += 50.f;
	Start.X += 200.f;

	//Forward Vector moves line out forward from where the actor is, and End Vector ends the line at 500 times the ForwardVector's start.
	FVector ForwardVector = GetActorForwardVector();
	FVector End = ((ForwardVector * 500.f) + Start);
	//create FCollision variable to use with line trace
	FCollisionQueryParams CollisionParams;

	//drawing the line for a visual rep of the line. Not Necessary, good for dev.
	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 5);

	//did it hit something?
	bool isHit = ActorLineTraceSingle(OutHit, Start, End, ECC_WorldStatic, CollisionParams);

	if (isHit)
	{
		if (GEngine)
		{
			//prints to screen the component name that outhit is pointing to.
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT("The Component being hit is: %s"), *OutHit.GetComponent()->GetName()));
		}
	}
}

