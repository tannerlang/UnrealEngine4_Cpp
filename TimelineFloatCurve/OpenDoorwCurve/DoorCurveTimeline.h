

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "DoorCurveTimeline.generated.h"

UCLASS()
class CPPWORLD_API ADoorCurveTimeline : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorCurveTimeline();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//creatiing vars and functions
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Door;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* DoorFrame;

	UPROPERTY(EditAnywhere)
	UCurveFloat* DoorCurve;

	UFUNCTION()
	void DoorControl();

	UFUNCTION()
	void DoorToggle();

	UFUNCTION()
	void SetState();

	bool Open;
	bool ReadyState;
	float RotateVal;
	float CurveFloatVal;
	float TimelineVal;
	FRotator DoorRotation;
	FTimeline MyTimeline;

};
