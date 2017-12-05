// Find something better to copy.

/*=============================================================================
HumanCombat.cpp: Implements the UHumanCombat class
=============================================================================*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HumanMovement.generated.h"

/**
*
*/
UCLASS()
class EXTROPY_API UHumanMovement : public UCharacterMovementComponent
{
	GENERATED_UCLASS_BODY()

	//--------------------------------
	// 
	//--------------------------------

public:

	/** Update crouch intent. */
	UFUNCTION()
	void SetCrouch(bool bCrouchIntent);

	/** */
	UFUNCTION()
	void SetSprint(bool bSprintIntent);

	/** */
	UFUNCTION()
	void Jump();

	/** */
	UFUNCTION()
	void Dodge(FVector2D MovementDirection);

	/** */
	UFUNCTION()
	void Roll(FVector2D MovementDirection);

	UFUNCTION()
	bool IsSprinting() const;

protected:

	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void PerformMovement(float DeltaSeconds) override;
	bool DoJump(bool bReplayingMoves) override;

private:

	UPROPERTY(Transient)
	bool bCrouchIntent;

	UPROPERTY(Transient)
	bool bDodgeIntent;

	UPROPERTY(Transient)
	bool bJumpIntent;

	UPROPERTY(Transient)
	bool bRollIntent;

	UPROPERTY(Transient)
	bool bSprintIntent;

	UPROPERTY(Transient)
	FVector2D DodgeDirection;

	/** Time server is using for this move, from timestamp passed by client */
	UPROPERTY(Transient)
	float CurrentServerMoveTime;

	//virtual bool DoDodge();

	/** Handle jump inputs */
	virtual void CheckJumpInput(float DeltaTime);
};
