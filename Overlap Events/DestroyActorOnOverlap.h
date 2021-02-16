// Fill out your copyright notice in the Description page of Project Settings.

//destroy actor on overlap events in UE4 can be used for picking up items in the world like ammo, health, etc... where the item is destroyed in the world when picked up.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestroyActorOnOverlap.generated.h"

UCLASS()
class CPPWORLD_API ADestroyActorOnOverlap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestroyActorOnOverlap();

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* MySphere;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* MyMesh;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	

};
