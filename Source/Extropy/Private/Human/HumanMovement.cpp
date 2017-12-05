// Find something better to copy.

/*=============================================================================
HumanMovement.cpp: Implements the UHumanMovement class
=============================================================================*/

#include "HumanMovement.h"
#include "Human.h"

//----------------------------------------------------------------------//
// UHumanMovement
//----------------------------------------------------------------------//

UHumanMovement::UHumanMovement(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NavAgentProps.bCanCrouch = true;

	bCrouchIntent = false;
	bDodgeIntent = false;
	bJumpIntent = false;
	bRollIntent = false;
	bSprintIntent = false;
}

void UHumanMovement::SetCrouch(bool bCrouchIntent)
{
	bCrouchIntent = bCrouchIntent;
}

void UHumanMovement::SetSprint(bool bSprintIntent)
{
	bSprintIntent = bSprintIntent;
}

void UHumanMovement::Jump()
{
	bJumpIntent = true;
}

void UHumanMovement::Dodge(FVector2D MovementDirection)
{
	bDodgeIntent = true;
	DodgeDirection = MovementDirection;
}

void UHumanMovement::Roll(FVector2D MovementDirection)
{
	bRollIntent = true;
	DodgeDirection = MovementDirection;
}

bool UHumanMovement::IsSprinting() const
{
	return false;
}

void UHumanMovement::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	const FVector InputVector = ConsumeInputVector();
	if (!HasValidData() || ShouldSkipUpdate(DeltaTime))
	{
		return;
	}

	UMovementComponent::TickComponent(DeltaTime, TickType, ThisTickFunction);
	AHuman* HumanOwner = Cast<AHuman>(CharacterOwner);

	const bool bLeftWorld = CharacterOwner->Role == ROLE_Authority && !CharacterOwner->CheckStillInWorld();
	if (!HasValidData() || UpdatedComponent->IsSimulatingPhysics() || bLeftWorld)
	{
		return;
	}

	if (CharacterOwner->Role > ROLE_SimulatedProxy)
	{
		// If we are a client we might have received an update from the server.
		const bool bIsClient = (GetNetMode() == NM_Client && CharacterOwner->Role == ROLE_AutonomousProxy);
		if (bIsClient)
		{
			ClientUpdatePositionAfterServerUpdate();
		}

		// Allow root motion to move characters that have no controller.
		if (CharacterOwner->IsLocallyControlled() || bRunPhysicsWithNoController || (!CharacterOwner->Controller && CharacterOwner->IsPlayingRootMotion()))
		{
			//UE_LOG(UTNet, Warning, TEXT("Correction COMPLETE velocity %f %f %f"), Velocity.X, Velocity.Y, Velocity.Z);
			// We need to check the jump state before adjusting input acceleration, to minimize latency
			// and to make sure acceleration respects our potentially new falling state.
			CheckJumpInput(DeltaTime);

			// apply input to acceleration
			Acceleration = ScaleInputAcceleration(ConstrainInputAcceleration(InputVector));
			AnalogInputModifier = ComputeAnalogInputModifier();

			if (CharacterOwner->Role == ROLE_Authority)
			{
				PerformMovement(DeltaTime);
			}
			else if (bIsClient)
			{
				ReplicateMoveToServer(DeltaTime, Acceleration);
			}
		}
		else if (CharacterOwner->GetRemoteRole() == ROLE_AutonomousProxy)
		{
			// Server ticking for remote client.
			// Between net updates from the client we need to update position if based on another object,
			// otherwise the object will move on intermediate frames and we won't follow it.
			MaybeUpdateBasedMovement(DeltaTime);
			SaveBaseLocation();
		}
		else if (!CharacterOwner->Controller && CharacterOwner->Role == ROLE_Authority)
		{
			// still update forces
			ApplyAccumulatedForces(DeltaTime);
			PerformMovement(DeltaTime);
		}
	}
	else if (CharacterOwner->Role == ROLE_SimulatedProxy)
	{
		AdjustProxyCapsuleSize();
		SimulatedTick(DeltaTime);
		CharacterOwner->RecalculateBaseEyeHeight();
	}
	if (bEnablePhysicsInteraction)
	{
		if (CurrentFloor.HitResult.IsValidBlockingHit())
		{
			// Apply downwards force when walking on top of physics objects
			if (UPrimitiveComponent* BaseComp = CurrentFloor.HitResult.GetComponent())
			{
				if (StandingDownwardForceScale != 0.f && BaseComp->IsAnySimulatingPhysics())
				{
					const float GravZ = GetGravityZ();
					const FVector ForceLocation = CurrentFloor.HitResult.ImpactPoint;
					BaseComp->AddForceAtLocation(FVector(0.f, 0.f, GravZ * Mass * StandingDownwardForceScale), ForceLocation, CurrentFloor.HitResult.BoneName);
				}
			}
		}
	}
}

void UHumanMovement::PerformMovement(float DeltaSeconds)
{
	/*
	if (!CharacterOwner)
	{
	return;
	}

	AExtropyCharacter* HumanOwner = Cast<AExtropyCharacter>(CharacterOwner);
	if (!HumanOwner || !HumanOwner->IsRagdoll())
	{
	FVector OldVelocity = Velocity;
	float RealGroundFriction = GroundFriction;
	if (Acceleration.IsZero())
	{
	GroundFriction = BrakingFriction;
	}
	if (bIsFloorSliding)
	{
	GroundFriction = 0.f;
	BrakingDecelerationWalking = BrakingDecelerationSliding;
	}
	else if (bWasFloorSliding && (MovementMode != MOVE_Falling))
	{
	Velocity *= FloorSlideEndingSpeedFactor;
	}
	bWasFloorSliding = bIsFloorSliding;

	bWantsToCrouch = bCrouchIntent || bIsSliding;
	FVector StartMoveLoc = GetActorLocation();
	*/
	bWantsToCrouch = bCrouchIntent;

	Super::PerformMovement(DeltaSeconds);
	//}
}

// TODO! Modifies jump behavior based on current movement state
bool UHumanMovement::DoJump(bool bReplayingMoves)
{
	return Super::DoJump(bReplayingMoves);
}

void UHumanMovement::CheckJumpInput(float DeltaTime)
{
	if (bJumpIntent)
	{
		DoJump(CharacterOwner->bClientUpdating);
		bJumpIntent = false;
	}
}