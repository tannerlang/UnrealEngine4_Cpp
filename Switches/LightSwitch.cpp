// Fill out your copyright notice in the Description page of Project Settings.


#include "LightSwitch.h"
#include "Components/PointLightComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ALightSwitch::ALightSwitch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//set light intensity
	LightIntensity = 3000.0f;

	//create upointlightcomponent and set as root
	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Point Light"));
	PointLight->Intensity = LightIntensity;
	PointLight->IsVisible();
	RootComponent = PointLight;


	//create uspherecomponent and attach to root. serves as the collision sphere when player is inside radius.
	SphereLight = CreateDefaultSubobject<USphereComponent>(TEXT("Light Sphere Component"));
	SphereLight->InitSphereRadius(400.f);
	SphereLight->SetCollisionProfileName(TEXT("Trigger"));
	SphereLight->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	SphereLight->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void ALightSwitch::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALightSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//toggle light function definition. toggle's light visibility.
void ALightSwitch::ToggleLight()
{
	PointLight->ToggleVisibility();
}