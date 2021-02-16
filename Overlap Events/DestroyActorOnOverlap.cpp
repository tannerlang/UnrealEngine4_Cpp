// Fill out your copyright notice in the Description page of Project Settings.


#include "DestroyActorOnOverlap.h"
#include "Components/SphereComponent.h"

// Sets default values
ADestroyActorOnOverlap::ADestroyActorOnOverlap()
{
 	
	MySphere = CreateDefaultSubobject<USphereComponent>(TEXT("My Sphere Component"));				//Creating component
	MySphere->InitSphereRadius(100.f);
	MySphere->SetCollisionProfileName(TEXT("Trigger"));
	RootComponent = MySphere;

	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Mesh"));
	MyMesh->SetupAttachment(RootComponent);

	MySphere->OnComponentBeginOverlap.AddDynamic(this, &ADestroyActorOnOverlap::OnOverlapBegin);	//Designating onoverlap begin with sphere.
}

// Called when the game starts or when spawned
void ADestroyActorOnOverlap::BeginPlay()
{
	Super::BeginPlay();
	
}

//defining onoverlapbegin function. What will happen to 'this' when overlapped.
void ADestroyActorOnOverlap::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Destroy();			
}





