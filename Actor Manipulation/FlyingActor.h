// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlyingActor.generated.h"

UCLASS()
class CPPWORLD_API AFlyingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFlyingActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//declaring float variables to use in the tick function in .cpp 
	float RunningTime;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float XVal;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float YVal;

	UPROPERTY(EditAnywhere, Category = "Movement")
		float ZVal;

};
