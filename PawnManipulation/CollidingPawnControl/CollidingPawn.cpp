//Colliding Pawn

#include "CollidingPawn.h"
#include "CollidingPawnMovementComp.h"
#include "UObject/ConstructorHelpers.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"



// Sets default values
ACollidingPawn::ACollidingPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

//----------------------------------------
//Creating Components

	//sphere will be the root of hierarchy because physics based
	USphereComponent* MySphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = MySphereComp;
	MySphereComp->InitSphereRadius(40.f);
	MySphereComp->SetCollisionProfileName(TEXT("Pawn"));
	
	//Creating static mesh for sphere
	UStaticMeshComponent* StaticSphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visual Sphere"));
	StaticSphere->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticSphereAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
		//If constructor helper succeeded, set up sphere and orientation
	if (StaticSphereAsset.Succeeded())
	{
		StaticSphere->SetStaticMesh(StaticSphereAsset.Object);
		StaticSphere->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
		StaticSphere->SetWorldScale3D(FVector(0.8f));	//Setting the scale to 80%, because a static mesh asset has a rdius of 50, and it needs to match the radius of MySphereComp. also move it down 40 UE units.
	}

	//creating particle system. attach it to StaticSphere not root, and offset from the mesh for visibility in game.
	MyParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Movement Particles"));
	MyParticleSystem->SetupAttachment(StaticSphere);
	MyParticleSystem->bAutoActivate = false;
	MyParticleSystem->SetRelativeLocation(FVector(-20.f, 0.f, 20.f));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleAsset(TEXT("/Game/StarterContent/Particles/P_Fire.P_Fire"));
	if (ParticleAsset.Succeeded())
	{
		MyParticleSystem->SetTemplate(ParticleAsset.Object);
	}

	//creating spring arm component for smooth camera work and can interact with boundries in game
	USpringArmComponent* SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
	SpringArm->TargetArmLength = 400.f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 3.0f;

	//creating the camera, attaching it to spring arm socket, not base.
	UCameraComponent* Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("The Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	//to be controlled by default player.
	AutoPossessPlayer = EAutoReceiveInput::Player0;


	//Creating Pawn movement comp: movement controller does not need to attach to component hierachy. Not a phyiscal object/scene component.
	MovementComp = CreateDefaultSubobject<UCollidingPawnMovementComp>(TEXT("MovementComp"));
	MovementComp->UpdatedComponent = RootComponent;
//---------------------------------------------

}

// Called when the game starts or when spawned
void ACollidingPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollidingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACollidingPawn::SetupPlayerInputComponent(class UInputComponent* InInputComponent)
{
	Super::SetupPlayerInputComponent(InInputComponent);
	

	//bindingInputs

	InInputComponent->BindAction("ToggleParticles", IE_Pressed, this, &ACollidingPawn::ToggleParticles);

	InInputComponent->BindAxis("MoveForward", this, &ACollidingPawn::MoveForward);
	InInputComponent->BindAxis("MoveRight", this, &ACollidingPawn::MoveRight);
	InInputComponent->BindAxis("Turn", this, &ACollidingPawn::Turn);
	



}

//-------------------------------------------------------------
//GetMovementComponent override function definition
UPawnMovementComponent* ACollidingPawn::GetMovementComponent() const
{
	//override returns the custom Movement Component from UCollidingPawnMovementComp component I made.
	return MovementComp;
}


//Pawn movement function definitions
void ACollidingPawn::MoveForward(float AxisVal)
{
	if (MovementComp && (MovementComp->UpdatedComponent == RootComponent))
	{
		MovementComp->AddInputVector(GetActorForwardVector() * AxisVal);
	}

}

void  ACollidingPawn::MoveRight(float AxisVal)
{
	if (MovementComp && (MovementComp->UpdatedComponent == RootComponent))
	{
		MovementComp->AddInputVector(GetActorRightVector() * AxisVal);
	}
}

void ACollidingPawn::Turn(float AxisVal)
{
	//gets rotation and changes it based on the new values
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += AxisVal;
	SetActorRotation(NewRotation);
}

void ACollidingPawn::ToggleParticles()
{
	//simply toggles the particle system
	if (MyParticleSystem && MyParticleSystem->Template)
	{
		MyParticleSystem->ToggleActive();
	}

}
//----------------------------------------------------------------