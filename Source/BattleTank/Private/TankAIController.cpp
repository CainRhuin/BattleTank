// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();

    auto PlayerTank = GetPlayerTank();
    auto ControlledTank = GetControlledTank();
    if (!ControlledTank)
    {
        UE_LOG(LogTemp, Error, TEXT("AIControlled can't possess!"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AIController possessing: %s"), *GetControlledTank()->GetName());
    }
    if (!PlayerTank)
    {
        UE_LOG(LogTemp, Error, TEXT("AIController can't find player tank"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AIController found player: %s"), *PlayerTank->GetName());
    }
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
}

ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
    auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
    if (!PlayerPawn)
    {return nullptr;}
    else
    {return Cast<ATank>(PlayerPawn);}
}