// Find something better to copy.

/*=============================================================================
HumanCombat.cpp: Implements the UHumanCombat class
=============================================================================*/

#pragma once

#include "CoreMinimal.h"
#include "ExtropyTypes.h"
#include "Components/ActorComponent.h"
#include "HumanCombat.generated.h"

class AWeapon;
class UAnimHumanInstance;
class UAnimMontage;

/**
* Defines montage to play based on weapon types in hand.
* !TODO Write test that asserts every possible weapon combination has a definition, and there are no duplicates.
*/
USTRUCT(BlueprintType)
struct FStanceDefinition
{
	GENERATED_BODY()

public:

	FStanceDefinition()
	{}

	/**  */
	UPROPERTY(BlueprintReadWrite, Category = "Weapon", EditAnywhere)
	EWeaponType LeftType;

	/**  */
	UPROPERTY(BlueprintReadWrite, Category = "Weapon", EditAnywhere)
	EWeaponType RightType;

	/**  */
	UPROPERTY(BlueprintReadWrite, Category = "Weapon", EditAnywhere)
	UAnimMontage* Montage;
};

/**
*
*/
UCLASS()
class EXTROPY_API UHumanCombat : public UActorComponent
{
	GENERATED_UCLASS_BODY()

	//--------------------------------
	// Inputs
	//--------------------------------

public:

	/** . */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void AssignSlot(AWeapon* Weapon, int32 Index, bool bOffHand = false);

	/** . */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void UseSlot(int32 Index);

	/** . */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void QueueAction(EActionType Type, bool bPressed);

	/** Process action queue. */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ProcessQueue(TArray<EActionModifier> MovementState);

	//--------------------------------
	// Notifies
	//--------------------------------

	/** Starts new decision window, clears existing triggers. */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void StartWindow(TArray<FActionTrigger> NewTriggers, FName DefaultNextSection);

	/** Adds triggers to existing window without affecting those already existing. */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void AddTriggers(TArray<FActionTrigger> NewTriggers);

	/** Ends decision window, jumps montage to trigger target section, or default if there was none. */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void EndWindow();

	/** . */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void Arm();

	/** . */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void Disarm();

	/** . */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void SwitchWeapon();

	//--------------------------------
	// Internal
	//--------------------------------
	
private:

	/** Container for weapon slot. */
	struct FWeaponSet
	{
		AWeapon* Left;
		AWeapon* Right;
		UAnimMontage* Montage;
	};

	TArray<FWeaponSet> Slots;

	/** . */
	UAnimMontage* FindMontage(const FWeaponSet& WeaponSet) const;

	/** Returns true if an input meets the trigger criteria. */
	bool ValidateTrigger(const FActionTrigger& Trigger) const;

	/** . */
	const static FName DefaultSection;

	/** . */
	const static FName DisarmSection;

	/** . */
	UPROPERTY(Transient)
	UAnimInstance* AnimInstance;

	/** . */
	UPROPERTY(Transient)
	UAnimMontage* AnimMontage;

	/** . */
	UPROPERTY(Transient)
	int32 ActiveSlot;

	/** . */
	UPROPERTY(Transient)
	int32 PendingSlot;

	/** . */
	UPROPERTY(Transient)
	FName NextSection;

	/** */
	UPROPERTY(Transient)
	TArray<FStanceDefinition> WeaponStances;

	/** . */
	UPROPERTY(Transient)
	TArray<FActionTrigger> Triggers;

	/** . */
	UPROPERTY(Transient)
	TArray<EActionType> Presses;

	/** . */
	UPROPERTY(Transient)
	TArray<EActionType> Held;

	/** . */
	UPROPERTY(Transient)
	TArray<EActionModifier> Modifiers;
};
