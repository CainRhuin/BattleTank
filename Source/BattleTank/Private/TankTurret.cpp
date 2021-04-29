// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
    auto Time = GetWorld()->GetTimeSeconds();
    RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);
    // move the barrel the right amount this frame
	// given a max elevation speed and the frame time
    auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    auto Rotation = GetRelativeRotation().Yaw + RotationChange;

    SetRelativeRotation(FRotator(0, Rotation, 0));
}
