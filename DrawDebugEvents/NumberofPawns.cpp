// Fill out your copyright notice in the Description page of Project Settings.


#include "NumberofPawns.h"

// Sets default values
ANumberofPawns::ANumberofPawns()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANumberofPawns::BeginPlay()
{
	Super::BeginPlay();
	
	int32 NumPawns = GetWorld()->GetNumPawns();

	//prints number of pawns in the world.
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("Number of Pawns: %d"), NumPawns));			
	}
}

// Called every frame
void ANumberofPawns::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

