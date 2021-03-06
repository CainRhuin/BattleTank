// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h" // so we can implement OnDeath
// Depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn* InPawn)
{
    Super::SetPawn(InPawn);
    if (InPawn)
    {
        auto PossessedTank = Cast<ATank>(InPawn);
        if (!PossessedTank) { return; }

        // Subscribe our local method to the tank's death event
        PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
    }
}

void ATankAIController::OnPossessedTankDeath()
{
    if (!GetPawn()) { return; }
    GetPawn()->DetachFromControllerPendingDestroy();
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
    auto ControlledTank = GetPawn();

    if (!(PlayerTank && ControlledTank)) { return; }
    
    // Move towards player
    MoveToActor(PlayerTank, AcceptanceRadius);

    // Aim towards player
    auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
    if (!ensure(AimingComponent)) { return; }

    AimingComponent->AimAt(PlayerTank->GetActorLocation());

    //if aiming or locked
    if (AimingComponent->GetFiringState() == EFiringState::Locked)
    {
        AimingComponent->Fire();// TODO Fix firing
    }
}