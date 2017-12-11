// Find something better to copy.

/*=============================================================================
HumanCombat.cpp: Implements the UHumanCombat class
=============================================================================*/

#pragma once

#include "CoreMinimal.h"
#include "ExtropyTypes.h"
#include "Item.h"
#include "Weapon.generated.h"

class USkeletalMeshComponent;

/**
* AWeapon is responsible for tracking combat state.
* It controls the weapon montage, processing inputs to determine next section.
* Human holds four loadouts, and is able to switch between them.
*/
UCLASS(BlueprintType, ClassGroup = "Combat")
class EXTROPY_API AWeapon : public AItem
{
	GENERATED_BODY()

public:

	/** . */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	EGripType GetGrip() const;

	/** . */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	EWeaponType GetType() const;

	/** . */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void Arm();

	/** . */
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void Disarm();

protected:

	/** . */
	UPROPERTY()
	USkeletalMeshComponent* WeaponMesh;

	/** . */
	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	FName HandSocket;

	/** . */
	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	FName HolsterSocket;

	/** . */
	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	EGripType Grip;

	/** . */
	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	EWeaponType Type;
};
