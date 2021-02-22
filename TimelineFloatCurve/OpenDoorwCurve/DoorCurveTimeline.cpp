// using timeline fstruct to open a door and close a door.


#include "DoorCurveTimeline.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADoorCurveTimeline::ADoorCurveTimeline()
{
	PrimaryActorTick.bCanEverTick = true;

	Open = false;
	ReadyState = true;

	//setup DoorFrame and set it as the root component.
	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
	RootComponent = DoorFrame;
	//attach door mesh 
	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Mesh"));
	Door->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ADoorCurveTimeline::BeginPlay()
{
	Super::BeginPlay();

	//setup timeline comp
	RotateVal = 1.0f;

	//doorcurve is set up in editor to float. if doorcurve is not null:
	if (DoorCurve)
	{
		//setup callback functions and link to timeline.
		FOnTimelineFloat TimelineCallback;
		FOnTimelineEventStatic TimelineFinishedCallback;
		//when timeline is moving through float curve, call DoorControl function. when timeline is finished, call SetState function.
		TimelineCallback.BindUFunction(this, FName("DoorControl"));
		TimelineFinishedCallback.BindUFunction(this, FName{ TEXT("SetState") });
		MyTimeline.AddInterpFloat(DoorCurve, TimelineCallback);
		MyTimeline.SetTimelineFinishedFunc(TimelineFinishedCallback);
	}
	
}

// Called every frame
void ADoorCurveTimeline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//link timeline to deltatime
	MyTimeline.TickTimeline(DeltaTime);

}

void ADoorCurveTimeline::DoorControl()
{
	//get playback pos of timeline, use that value from the float curve to set door's rotation.
	TimelineVal = MyTimeline.GetPlaybackPosition();
	CurveFloatVal = RotateVal * DoorCurve->GetFloatValue(TimelineVal);		//rotateval is set in ToggleDoor(), used here.

	FQuat NewRotation = FQuat(FRotator(0.f, CurveFloatVal, 0.f));
	Door->SetRelativeRotation(NewRotation);
}

void ADoorCurveTimeline::SetState()
{
	//set readystate to true. Can only open when is true.
	ReadyState = true;
}

void ADoorCurveTimeline::DoorToggle()
{
	if (ReadyState)
	{
		//toggle open, get door's curr rotation, get player direction, if open is true, set rotate val depending on direction, toggle readystate.
		Open = !Open;
		DoorRotation = Door->GetRelativeRotation();

		APawn* Player = UGameplayStatics::GetPlayerPawn(this, 0);
		FVector PlayerLocation = Player->GetActorLocation();
		FVector Direction = GetActorLocation() - PlayerLocation;
		Direction = UKismetMathLibrary::LessLess_VectorRotator(Direction, GetActorRotation());

		if (Open)
		{
			if (Direction.X > 0.0f)
			{
				RotateVal = 1.0f;
			}
			else
			{
				RotateVal = -1.0f;
			}
			ReadyState = false;
			MyTimeline.PlayFromStart();
		}
		// if open is false, set readystate to false and reverse timeline.
		else
		{
			ReadyState = false;
			MyTimeline.Reverse();
		}
	}
}

