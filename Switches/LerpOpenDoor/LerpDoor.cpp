// Fill out your copyright notice in the Description page of Project Settings.


#include "LerpDoor.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"

// Sets default values
ALerpDoor::ALerpDoor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Open = false;
	
	//component set ups.
	DoorBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	DoorBox->InitBoxExtent(FVector(50, 50, 50));
	RootComponent = DoorBox;

	Door = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("Door"));
	Door->SetRelativeLocation(FVector(0.0f, 50.f, -50.f));
	Door->SetupAttachment(RootComponent);

	//bind overlap function
	DoorBox->OnComponentBeginOverlap.AddDynamic(this, &ALerpDoor::OnOverlapBegin);
	DoorBox->OnComponentEndOverlap.AddDynamic(this, &ALerpDoor::OnOverlapEnd);


}

// Called when the game starts or when spawned
void ALerpDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALerpDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DoorRotation = Door->GetRelativeRotation();
	//check if the door is open, run lerp function. Lerp functions only run in tick function.
	//lerp function takes two FQauts, which represents rotation about an axis in 3D space, and interpolates between them. it passes alpha last which ranges from 0-1.
	//gives a smooth opening because it is lerp(fquat(FRotator)) and not just lerp(FRotator).
	if (Open)
	{
		Door->SetRelativeRotation(FMath::Lerp(FQuat(DoorRotation), FQuat(FRotator(0.0f, RotateVal, 0.0f)), 0.01f));
	}
	else
	{
		Door->SetRelativeRotation(FMath::Lerp(FQuat(DoorRotation), FQuat(FRotator(0.0f, 0.0f, 0.0f)), 0.01f));
	}
}

//overlap functions
void ALerpDoor::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		//get player and actor facing directions. LessLess_VectorRotator() to assign Direction the result of Direction rotated by the inverse of ActorRotation to account for parent component rotation.
		FVector PlayerLocation = OtherActor->GetActorLocation();
		FVector Direction = GetActorLocation() - PlayerLocation;
		Direction = UKismetMathLibrary::LessLess_VectorRotator(Direction, GetActorRotation());

		if (Direction.X > 0.0f)
		{
			RotateVal = 90.f;
		}
		else
		{
			RotateVal = -90.f;
		}

		Open = true;
	}
}

void ALerpDoor::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		Open = false;
	}
}