// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//--------------
	//box comp setup
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComp->InitBoxExtent(FVector(150, 100, 100));
	BoxComp->SetCollisionProfileName("Trigger");
	RootComponent = BoxComp;

	MyDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyDoor"));
	MyDoor->SetupAttachment(RootComponent);

	//get the door model
	static ConstructorHelpers::FObjectFinder<UStaticMesh> DoorAsset(TEXT("/Game/StarterContent/Props/SM_Door.SM_Door"));
	//create and set the properties
	if (DoorAsset.Succeeded())
	{
		MyDoor->SetStaticMesh(DoorAsset.Object);
		MyDoor->SetRelativeLocation(FVector(0.f, 50.f, -100.f));
		MyDoor->SetWorldScale3D(FVector(1.f));
	}

	

}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();

	//draw debug box
	DrawDebugBox(GetWorld(), GetActorLocation(), BoxComp->GetScaledBoxExtent(), FQuat(GetActorRotation()), FColor::White, true, -1, 0, 2);
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//check if door is opening or closing, runs appropriate function, pass delta time.
	if (Opening)
	{
		OpenDoor(DeltaTime);
	}
	if (Closing)
	{
		CloseDoor(DeltaTime);
	}
}

void ADoor::OpenDoor(float DeltaTime)
{
	//get the yaw value of the door.
	CurrRotation = MyDoor->GetRelativeRotation().Yaw;
	//add how much rotation per fram
	AddRotation = PosNeg * DeltaTime * 80;

	//if statement checks if yaw is near max, then switches bool statements to false to stop movement.
	if (FMath::IsNearlyEqual(CurrRotation, Max, 1.5f))
	{
		Closing = false;
		Opening = false;
	}
	else if (Opening)
	{
		FRotator NewRotation = FRotator(0.f, AddRotation, 0.f);
		MyDoor->AddRelativeRotation(FQuat(NewRotation), false, 0, ETeleportType::None);
	}
}

void ADoor::CloseDoor(float DeltaTime)
{
	CurrRotation = MyDoor->GetRelativeRotation().Yaw;

	//if statement to determine how much rotation to add to door.
	if (CurrRotation > 0)
	{
		AddRotation = -DeltaTime * 80;
	}
	else
	{
		AddRotation = DeltaTime * 80;
	}

	//if yaw is near 0 or the min
	if (FMath::IsNearlyEqual(CurrRotation, 0.f, 1.5f))
	{
		Closing = false;
		Opening = false;
	}
	else if (Closing)
	{
		FRotator NewRotation = FRotator(0.f, AddRotation, 0.f);
		MyDoor->AddRelativeRotation(FQuat(NewRotation), false, 0, ETeleportType::None);
	}
}

//called from character.
void ADoor::ToggleDoor(FVector ForwardVector)
{
	//in front or behind door. character forwardvector camera passed with boxcomp to get DotP.
	DotP = FVector::DotProduct(BoxComp->GetForwardVector(), ForwardVector);

	//1 or -1 from the dot product depending on if DotP is pos or neg
	PosNeg = FMath::Sign(DotP);

	//degree clamp. Max is set accordingly to the player's position.
	Max = PosNeg * 90.0f;

	//toggle
	if (IsClosed)
	{
		IsClosed = false;
		Closing = false;
		Opening = true;
	}
	else
	{
		Opening = false;
		IsClosed = true;
		Closing = true;
	}
}