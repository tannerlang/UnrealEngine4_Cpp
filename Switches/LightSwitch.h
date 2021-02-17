// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightSwitch.generated.h"

UCLASS()
class CPPWORLD_API ALightSwitch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightSwitch();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	//declaring the 4 members needed
	//point light comp declaration
	UPROPERTY(VisibleAnywhere, Category = "Light Switch")
	class UPointLightComponent* PointLight;

	//sphere comp declaration
	UPROPERTY(VisibleAnywhere, Category = "Light Switch")
	class USphereComponent* SphereLight;

	//light intensity variable declaration
	UPROPERTY(VisibleAnywhere, Category = "Light Switch")
	float LightIntensity;

	//toggle light function declaration
	UFUNCTION(BlueprintCallable, Category = "Light Switch")
	void ToggleLight();
};
