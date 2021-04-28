// Fill out your copyright notice in the Description page of Project Settings.

// #include "Engine/World.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();

    auto ControlledTank = GetControlledTank();
    if (!ControlledTank) 
    {
        UE_LOG(LogTemp, Error, TEXT("PlayerController not possessing a tank"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController Possessing: %s"), *ControlledTank->GetName());
    }
}

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if (!GetControlledTank()){return;}

    FVector HitLocation; // Out Param

    if (GetSightRayHitLocation(HitLocation))
    {
        // UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *HitLocation.ToString());
        GetSightRayHitLocation(HitLocation);

        // TODO tell controlled tank to aim at this point
    }
}

// Get world location of linetrace through crosshair, true if it hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
    // Find crosshair position
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);

    auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

    // de-project screen position of the crosshair to a world direction
    FVector LookDirection;
    if (GetLookDirection(ScreenLocation, LookDirection))
    {
        UE_LOG(LogTemp, Warning, TEXT("WorldDirection is: %s"), *LookDirection.ToString()); // LOG TEST to check if WorldDirection is working...
    }
    // line trace along that look direction and see what we hit (up to max range)
    return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
    FVector WorldLocation; // Useless Data, discarded
    return DeprojectScreenPositionToWorld
        (
        ScreenLocation.X,
        ScreenLocation.Y,
        WorldLocation, 
        LookDirection
        );        
}