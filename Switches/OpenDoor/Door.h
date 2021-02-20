// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

UCLASS()
class CPPWORLD_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	//----------------
	//door members 
	UFUNCTION()
	void OpenDoor(float DeltaTime);

	UFUNCTION()
	void CloseDoor(float DeltaTime);

	class UStaticMeshComponent* MyDoor;

	//box comp 
	UPROPERTY(VisibleAnywhere, Category = "BoxComp")
	class UBoxComponent* BoxComp;

	UFUNCTION()
	void ToggleDoor(FVector ForwardVector);

	//set defaults
	bool Opening = false;
	bool Closing = false;
	bool IsClosed = true;

	float DotP = 0.f;
	float Max = 0.f;
	float AddRotation = 0.f;
	float PosNeg = 0.f;
	float CurrRotation = 0.f;





};
