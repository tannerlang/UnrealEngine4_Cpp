// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerInputPawn.generated.h"

UCLASS()
class CPPWORLD_API APlayerInputPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerInputPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	USceneComponent* VisibleComp;

	//creating variables for axis movements.
	//input functions
	void Move_XAxis(float AxisVal);
	void Move_YAxis(float AxisVal);
	void StartGrow();
	void StopGrow();
	//input vars
	FVector CurrentVelocity;
	bool bGrowing;
};
