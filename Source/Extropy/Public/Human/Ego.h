// Find something better to copy.

/*=============================================================================
HumanCombat.cpp: Implements the UHumanCombat class
=============================================================================*/

/*=============================================================================
Human.cpp: Implements the UHumanCombat class
=============================================================================*/

#pragma once

#include "CoreMinimal.h"
#include "ExtropyTypes.h"
#include "GameFramework/PlayerController.h"
#include "Ego.generated.h"

class AHuman;

/**
*
*/
UCLASS()
class EXTROPY_API AEgo : public APlayerController
{
	GENERATED_UCLASS_BODY()

	//--------------------------------
	// Exposed attributes
	//--------------------------------

public:

	/** Base look left/right rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseYawRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BasePitchRate;

	/** Max time between input press and release to be considered a tap.. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float MaxTapTime;

	//--------------------------------
	// Transient variables
	//--------------------------------

private:

	/** Holds possessed ExtropyCharacter. */
	UPROPERTY()
	AHuman* HumanPawn;

	/** Holds value of vertical movement until input update. */
	UPROPERTY(Transient)
	float VerticalMovement;

	/** Holds value of horizontal movement until input update. */
	UPROPERTY(Transient)
	float HorizontalMovement;

	/** Stores time of most recent roll press to determine taps. */
	UPROPERTY(Transient)
	float RollPressTime;

	/** Stores time of most recent dodge press to determine taps. */
	UPROPERTY(Transient)
	float DodgePressTime;

	//--------------------------------
	// Internal functions
	//--------------------------------

	/** Called for forward/backward input. */
	virtual void AddVerticalInput(float Value);

	/** Called for left/right input. */
	virtual void AddHorizontalInput(float Value);

	/**
	* Called via input to turn look up/down at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	virtual void PitchAtRate(float Rate);

	/**
	* Called via input to turn at a given rate.
	* @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	virtual void YawAtRate(float Rate);

	/** Called when jump is pressed. */
	virtual void JumpPressed();

	/** Called when crouch is pressed. */
	virtual void CrouchPressed();

	/** Called when crouch is released. */
	virtual void CrouchReleased();

	/** Called when sprint is pressed. */
	virtual void SprintPressed();

	/** Called when sprint is released. */
	virtual void SprintReleased();

	/** Called when left weapon is pressed. */
	virtual void WeaponLeftPressed();

	/** Called when left weapon is released. */
	virtual void WeaponLeftReleased();

	/** Called when right weapon is pressed. */
	virtual void WeaponRightPressed();

	/** Called when right weapon is released. */
	virtual void WeaponRightReleased();

	/** Called when ability 1 is pressed. */
	virtual void Ability1Pressed();

	/** Called when ability 1 is released. */
	virtual void Ability1Released();

	/** Called when ability 2 is pressed. */
	virtual void Ability2Pressed();

	/** Called when ability 2 is released. */
	virtual void Ability2Released();

	/** Called when ability 3 is pressed. */
	virtual void Ability3Pressed();

	/** Called when ability 3 is released. */
	virtual void Ability3Released();

	/** Called when ability 4 is pressed. */
	virtual void Ability4Pressed();

	/** Called when ability 4 is released. */
	virtual void Ability4Released();

	/** Called when Loadout slot 1 is pressed. */
	virtual void Loadout1Pressed();

	/** Called when Loadout slot 2 is pressed. */
	virtual void Loadout2Pressed();

	/** Called when Loadout slot 3 is pressed. */
	virtual void Loadout3Pressed();

	/** Called when Loadout slot 4 is pressed. */
	virtual void Loadout4Pressed();

	/** Called when Interact is pressed. */
	virtual void Interact();

	//--------------------------------
	// Overrides
	//--------------------------------

public:

	virtual void SetPawn(APawn* InPawn) override;
	virtual void SetupInputComponent() override;
	virtual void ProcessPlayerInput(const float DeltaTime, const bool bGamePaused) override;
};
