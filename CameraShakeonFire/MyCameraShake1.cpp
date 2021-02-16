// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCameraShake1.h"

//default vals
UMyCameraShake1::UMyCameraShake1()
{
	OscillationDuration = 0.12f;
	OscillationBlendInTime = 0.025f;
	OscillationBlendOutTime = 0.025f;

	//setting oscillation values to be random within a range
	RotOscillation.Pitch.Amplitude = FMath::RandRange(2.5f, 5.0f);
	RotOscillation.Pitch.Frequency = FMath::RandRange(12.0f, 17.0f);

	RotOscillation.Yaw.Amplitude = FMath::RandRange(2.5f, 5.0f);
	RotOscillation.Yaw.Frequency = FMath::RandRange(12.0f, 17.0f);
}