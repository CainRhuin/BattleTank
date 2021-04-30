// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

	// TODO prevent double speed due to dual control use
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
	// TODO prevent double speed due to dual control use
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// Do Not Call Super
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	auto ForwardMovement = FVector::DotProduct(AIForwardIntention, TankForward);
	IntendMoveForward(ForwardMovement);

	auto RightMovement = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	IntendTurnRight(RightMovement);
 
	// UE_LOG(LogTemp, Warning, TEXT("%s vectoring to : %s"), *TankName, *MoveVelocityString);
}