// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::AimAt(FVector WorldSpaceAim, float LaunchSpeed)
{
	if (!Barrel){return;}

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this, 
		OutLaunchVelocity, 
		StartLocation, 
		WorldSpaceAim, 
		LaunchSpeed,
		false,
		0.f,
		0.f, 
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (bHaveAimSolution)
	{
	auto AimDirection = OutLaunchVelocity.GetSafeNormal();
	MoveBarrelTowards(AimDirection);
	auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f: Aim Solution Found"), Time);
	}
	else
	{
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: No aim solve found"), Time);
	}
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// work out difference between current barrel rotation and aimdirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(5); // TODO remove magic number
}