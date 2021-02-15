// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerActor.h"
#include "TimerManager.h"

// Sets default values
ATimerActor::ATimerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATimerActor::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(MemberTimerHandle, this, &ATimerActor::Repeating, 2.f, true, 5.f);
}

// Called every frame
void ATimerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATimerActor::Repeating()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("What's Up"));
	}
}

