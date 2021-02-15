// Fill out your copyright notice in the Description page of Project Settings.


#include "PracCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
APracCharacter::APracCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));												//Creates the capsule trigger capsule.
	TriggerCapsule->InitCapsuleSize(55.f, 96.f);																						//Initialize capsule size to the standard FirstPerson size
	TriggerCapsule->SetCollisionProfileName(TEXT("Trigger"));																			//Gives component similar overlap events to a trigger capsule.
	TriggerCapsule->SetupAttachment(RootComponent);																						//Attaches Trigger capsule to root component.

	TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &APracCharacter::OnOverlapBegin);											//Connecting capsule to overlap events.
	TriggerCapsule->OnComponentEndOverlap.AddDynamic(this, &APracCharacter::OnOverlapEnd);
}

// Called when the game starts or when spawned
void APracCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APracCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APracCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

//On Overlap Begin Function
void APracCharacter::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap Begin"));													//Prints OverlapBegin Debug Message when triggered

		}
	}
}

//On Overlap End Function
void APracCharacter::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (GEngine)																														//Don't need first if statement from OnOverlapBegin(). Just Checks if it ends.
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap End"));													//Prints OverlapEnd Debug Message when triggered

	}
}