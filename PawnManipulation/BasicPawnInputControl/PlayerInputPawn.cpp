// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInputPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APlayerInputPawn::APlayerInputPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//--------
	//set pawn to controlled by lowest numbered player
	AutoPossessPlayer = EAutoReceiveInput::Player0;

	//create dummy root comp to attach things to
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	//creating camera and visible obj
	UCameraComponent* MyCam = CreateDefaultSubobject<UCameraComponent>(TEXT("My Camera"));
	VisibleComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visible Object"));
	//attaching cam and visible obj to root comp. adjusting camera. 
	MyCam->SetupAttachment(RootComponent);
	MyCam->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));		//Setrelativelocation and rotation are member functions of USceneComponent class: UCameraComponent is derived from USceneComponent.
	MyCam->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	VisibleComp->SetupAttachment(RootComponent);
	//--------



}

// Called when the game starts or when spawned
void APlayerInputPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerInputPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//--------
	//grow and shrink based on GROW action input.
	{
		float CurrentScale = VisibleComp->GetComponentScale().X;
		if (bGrowing)
		{
			//Grow over the course of one second
			CurrentScale += DeltaTime;
		}
		else
		{
			//shrink half as fast as it grew
			CurrentScale -= (DeltaTime * 0.5f);
		}
		//clamp to ensure shrink never goes below the starting size, or increase more than double the size.
		CurrentScale = FMath::Clamp(CurrentScale, 1.0f, 2.0f);
		VisibleComp->SetWorldScale3D(FVector(CurrentScale));
	}
	//move based on .h move members.
	{
		if (!CurrentVelocity.IsZero())
		{
			FVector ChangedLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
			SetActorLocation(ChangedLocation);
		}
	}
	//--------
}

// Called to bind functionality to input
void APlayerInputPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//---------
	//when grow key is pressed and released
	InputComponent->BindAction("Grow", IE_Pressed, this, &APlayerInputPawn::StartGrow);
	InputComponent->BindAction("Grow", IE_Released, this, &APlayerInputPawn::StopGrow);
	
	//Moves every frame in respons to vals of the two movement axis, x and y.
	InputComponent->BindAxis("MoveX", this, &APlayerInputPawn::Move_XAxis);
	InputComponent->BindAxis("MoveY", this, &APlayerInputPawn::Move_YAxis);
	//---------
}

//--------
//member function defs
void APlayerInputPawn::StartGrow()
{
	bGrowing = true;
}

void APlayerInputPawn::StopGrow()
{
	bGrowing = false;
}

void APlayerInputPawn::Move_XAxis(float AxisVal)
{
	//move 150 UE u/s forward or backward
	CurrentVelocity.X = FMath::Clamp(AxisVal, -1.0f, 1.0f) * 150.0f;
}

void APlayerInputPawn::Move_YAxis(float AxisVal)
{
	//move 150 UE u/s left or right
	CurrentVelocity.Y = FMath::Clamp(AxisVal, -1.0f, 1.0f) * 150.0f;
}
//--------