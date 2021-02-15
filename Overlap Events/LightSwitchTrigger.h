// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightSwitchTrigger.generated.h"


class UPointLightComponent;
class USphereComponent;


UCLASS()
class CPPPRACTICE_API ALightSwitchTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightSwitchTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	//declare point light component
	UPROPERTY(VisibleAnywhere, Category = "Light Switch")
	class UPointLightComponent* PointLight;

	//declare sphere component
	UPROPERTY(VisibleAnywhere, Category = "Light Switch")
	class USphereComponent* LightSphere;

	//declare light intensity var
	UPROPERTY(VisibleAnywhere, Category = "Light Switch")
	float LightIntensity;
	
	//overlap begin declaration
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//overlap end declaration
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OVerlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//ToggleLight function declaration
	UFUNCTION()
	void ToggleLight();
};
