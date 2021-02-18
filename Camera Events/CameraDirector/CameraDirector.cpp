// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraDirector.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACameraDirector::ACameraDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraDirector::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//manages time between camera changes and create blent time var for transitioning to cam 2.
	const float TimeBetweenCameraChange = 2.f;
	const float SmoothBlendTime = 0.75f;

	//remove deltatime from CameraChangeTime variable
	CameraChangeTime -= DeltaTime;

	if (CameraChangeTime <= 0.0f)
	{
		CameraChangeTime += TimeBetweenCameraChange;

		//getting the player controller to set its view target. 
		APlayerController* MyPlayerController = UGameplayStatics::GetPlayerController(this, 0);
		//checking the view target, and switching between cameras depending on target.
		if (CameraTwo && (MyPlayerController->GetViewTarget() == CameraOne))
		{
			//blend to cam two
			MyPlayerController->SetViewTargetWithBlend(CameraTwo, SmoothBlendTime);
		}
		else if (CameraOne)
		{
			MyPlayerController->SetViewTarget(CameraOne);
		}
	}
}

