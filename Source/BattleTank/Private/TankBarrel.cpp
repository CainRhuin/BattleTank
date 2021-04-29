// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
    auto Time = GetWorld()->GetTimeSeconds();
    RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);
    // move the barrel the right amount this frame
	// given a max elevation speed and the frame time
    auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    auto RawNewElevation = GetRelativeRotation().Pitch + ElevationChange;
    auto Elevation = FMath::Clamp<float>(RawNewElevation, MinDegreesOfElevation, MaxDegreesOfElevation);

    SetRelativeRotation(FRotator(Elevation, 0, 0));
}