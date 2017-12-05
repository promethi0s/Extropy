// Find something better to copy.

/*=============================================================================
Human.h: Implements the AHuman class
=============================================================================*/

#pragma once

#include "Extropy.h"
#include "ExtropyTypes.h"
#include "GameFramework/Character.h"
#include "Human.generated.h"

class UAnimInstance;
class UCameraComponent;
class UHumanCombat;
class UHumanMovement;
class USkeletalMeshComponent;

/**
* 
*/
UCLASS()
class EXTROPY_API AHuman : public ACharacter
{
	GENERATED_UCLASS_BODY()

	//--------------------------------
	// Movement
	//--------------------------------

public:

	void Crouch(bool bClientSimulation = false) override { StartCrouch(); }
	void UnCrouch(bool bClientSimulation = false) override { StopCrouch(); }

	/** Attempt to start crouching. */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void StartCrouch();

	/** Attempt to stop crouching. */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void StopCrouch();

	/** Attempt to start sprinting. */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void StartSprint();

	/** Attempt to stop sprinting. */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void StopSprint();

	/** Attempt to jump. */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void Jump() override;

	/** Attempt to dodge. */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void Dodge();
	
	/** Attempt to roll. */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	void Roll();

	//--------------------------------
	// Combat
	//--------------------------------

	// Inputs

	/** Register an action press of given type. */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void QueueWeaponInput(EActionType Type, bool bPressed);

	/** Process action queue. */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ProcessDeferredInputs(FVector2D MovementDirection);

	/** Arms loadout. If already active, disarms instead. */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void UseWeaponLoadout(int32 Index);

	// Notifies

	/** Starts new decision window, clears existing triggers. */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void StartDecisionWindow(TArray<FActionTrigger> NewTriggers, FName DefaultNextSection);

	/** Adds triggers to existing window without affecting those already existing. */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void AddCombatTriggers(TArray<FActionTrigger> NewTriggers);

	/** Ends decision window, jumps montage to trigger target section, or default if there was none. */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void EndDecisionWindow();

	/** Detaches weapon mesh from holster socket, attaches to hand. */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void DrawWeapon();

	/** Detaches weapon mesh from hand socket, attaches to holster. */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void HolsterWeapon();

	/** Clears pointer to active weapon, arms pending weapon. */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void DisarmWeapon();

	/** Triggers projectile spawn, magic or item use, etc. May end up separating into multiple functions. */
	//UFUNCTION(BlueprintCallable, Category = "Notify | Combat")
	//void PerformSkill();
	//float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	bool IsDead() const { return false; }
	//ExecuteMeleeAttack()
	//ExecuteRangeAttack()	
	/** */
	// UFUNCTION()
	// FHumanInjuries GetInjuries();

	//--------------------------------
	// Inventory
	//--------------------------------

	/**  */
	UFUNCTION(BlueprintCallable, Category = "Input")
		void Interact();

	/** . */
	UAnimInstance* GetAnimInstance() const;

	/** . */
	USkeletalMeshComponent* GetMesh() const;

	/** . */
	UFUNCTION(BlueprintCallable, Category = Mesh)
	virtual bool IsFirstPerson() const;

	/** . */
	bool IsAlive() const;

	//--------------------------------
	// Inventory
	//--------------------------------

	/** . */
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Pawn")
	virtual bool AddToInventory(AItem* ItemToAdd, bool bAutoActivate);

	/** . */
	bool IsInInventory(const AItem* ItemToCheck) const;

	/** . */
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Pawn")
	virtual void RemoveFromInventory(AItem* ItemToRemove);

	/** toss an inventory item in the direction the player is facing
	* (the inventory must have a pickup defined)
	* ExtraVelocity is in the reference frame of the character (X is forward)
	*/
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "Pawn")
	virtual void TossItem(AItem* ItemToToss, FVector ExtraVelocity = FVector::ZeroVector);

	//--------------------------------
	// Components
	//--------------------------------

private:

	/** */
	UPROPERTY(Transient)
	UHumanCombat* HumanCombat;

	/** */
	UPROPERTY(Transient)
	UHumanMovement* HumanMovement;

	/** */
	UPROPERTY(Transient)
	UCameraComponent* Camera1P;

	/** */
	UPROPERTY(Transient)
	USkeletalMeshComponent* Mesh1P;

	/** */
	UPROPERTY(Transient)
		TArray<AItem*> Inventory;

	//--------------------------------
	// Transient
	//--------------------------------

protected:

	/** . */
	UPROPERTY(Transient)
	bool bDodgeIntent;

	/** . */
	UPROPERTY(Transient)
	bool bRollIntent;

	//--------------------------------
	// Internal
	//--------------------------------
};
