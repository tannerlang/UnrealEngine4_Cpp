// Fill out your copyright notice in the Description page of Project Settings.


#include "FindPlayerPosition.h"

// Sets default values
AFindPlayerPosition::AFindPlayerPosition()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFindPlayerPosition::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFindPlayerPosition::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//gets first player pawn location. MyCharacter = to the the location of the pawn at a given tick.
	FVector MyCharacter = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	//Prints player location to screen.
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Player Location: %s"), *MyCharacter.ToString()));
	}
	//DebugMessage function takes the default value -1 and the length of time it prints, the color, and the message to print which converts the vector to a STRING.
}

