// Fill out your copyright notice in the Description page of Project Settings.


#include "LightSwitchTrigger.h"
#include "Components/PointLightComponent.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/SceneComponent.h"

// Sets default values
ALightSwitchTrigger::ALightSwitchTrigger()
{
	LightIntensity = 3000.0f;

	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Point Light"));		//Creating Component
	PointLight->Intensity = LightIntensity;												//Adding intensity
	PointLight->IsVisible();															//The light is visible to start.											
	RootComponent = PointLight;	

	LightSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Light Sphere Component"));
	LightSphere->InitSphereRadius(300.0f);
	LightSphere->SetCollisionProfileName(TEXT("Trigger"));
	LightSphere->SetupAttachment(RootComponent);


	//Designating overlap functions as a delegate called when an actor overlaps the light sphere.
	LightSphere->OnComponentBeginOverlap.AddDynamic(this, &ALightSwitchTrigger::OnOverlapBegin);
	LightSphere->OnComponentEndOverlap.AddDynamic(this, &ALightSwitchTrigger::OnOverlapEnd);


}

// Called when the game starts or when spawned
void ALightSwitchTrigger::BeginPlay()
{
	Super::BeginPlay();

	//Adding debug sphere with the same radius as the lightsphere, helps see where the area of overlap starts.
	DrawDebugSphere(GetWorld(), GetActorLocation(), 300.f, 50, FColor::Green, true, 999, 0, 2);	
	
}

//Overlap Function Def
void ALightSwitchTrigger::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		ToggleLight();
	}
}
//Overlap Function Def
void ALightSwitchTrigger::OnOverlapEnd(class UPrimitiveComponent* OVerlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		ToggleLight();
	}
}

void ALightSwitchTrigger::ToggleLight()
{
	PointLight->ToggleVisibility();
}