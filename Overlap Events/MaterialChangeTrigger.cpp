// Fill out your copyright notice in the Description page of Project Settings.

#include "MaterialChangeTrigger.h"
#include "DrawDebugHelpers.h"
#include "Components/BoxComponent.h"


// Sets default values
AMaterialChangeTrigger::AMaterialChangeTrigger()
{


	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMesh"));								//Creates static mesh.
	RootComponent = MyMesh;

	MyBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("MyBoxComponent"));						//Creates the box component.
	MyBoxComponent->InitBoxExtent(FVector(400));														//Use InitBoxExtent to set the the box component's extent to 400x400x400.
	MyBoxComponent->SetCollisionProfileName("Trigger");													//BoxComp initializes with the collision profile name Trigger
	MyBoxComponent->SetupAttachment(RootComponent);														//Attaches box comp to root component.


	MaterialOn = CreateDefaultSubobject<UMaterial>(TEXT("Material On"));
	MaterialOff = CreateDefaultSubobject<UMaterial>(TEXT("Material Off"));								//Creating the two materials to switch the mesh between.

	MyBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AMaterialChangeTrigger::OnOverlapBegin);	//
	
}

// Called when the game starts or when spawned
void AMaterialChangeTrigger::BeginPlay()
{
	Super::BeginPlay();

	DrawDebugBox(GetWorld(), GetActorLocation(), FVector(400), FColor::White, true, -1, 0, 10);			//Draw debug box and set the first material.

	MyMesh->SetMaterial(0, MaterialOff);																//Setting the first material for the mesh.
	
}

// Called every frame
void AMaterialChangeTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMaterialChangeTrigger::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr ) && (OtherActor !=this) && (OtherComp != nullptr))
	{
		MyMesh->SetMaterial(0, MaterialOn);																//Overlap function changes the mesh material from MaterialOff to MaterialOn when overlap.
	}
}