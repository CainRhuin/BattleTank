// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
    auto Time = GetWorld()->GetTimeSeconds();
    RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);

    auto RotationChange = RelativeSpeed * RotationDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    SetRelativeRotation(FRotator(0, 0, RotationChange));
}

