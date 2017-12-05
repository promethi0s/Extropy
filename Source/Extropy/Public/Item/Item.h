// Find something better to copy.						

/*=============================================================================
Item.h: Implements the AItem class
=============================================================================*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class AHuman;
class UMeshComponent;
class UShapeComponent;
class UProjectileMovement;

/**
* Base class for all inventory items.
* @see AWeapon, AArmor, AQuestItem, AConsumable, AAmmo
*/
UCLASS()
class EXTROPY_API AItem : public AActor
{
	GENERATED_BODY()

	//--------------------------------
	// Interface
	//--------------------------------

public:

	/** . */
	UFUNCTION()
	virtual void OnPickup(AHuman* NewOwner);

	/** . */
	UFUNCTION()
	virtual void OnDrop();

	/** . */
	UFUNCTION()
	void Equip();

	/** . */
	UFUNCTION()
	void Unequip();

	/** . */
	UFUNCTION()
	void AttachMesh(FName Socket);

	/** . */
	UFUNCTION()
	void DetachMesh();

	//--------------------------------
	// Attributes
	//--------------------------------

protected:

	/** If true, cannot be removed from inventory. */
	UPROPERTY()
	bool bLocked;

	/** If true, cannot be stacked in inventory. */
	UPROPERTY()
	bool bUnique;

	/** Weight in pounds. */
	UPROPERTY()
	float Weight;

	/** Unique identifier. */
	UPROPERTY()
	FName ID;

	/** Value in bronze. */
	UPROPERTY()
	int32 Value;

	//--------------------------------
	// Components
	//--------------------------------

private:

	/** . */
	UPROPERTY()
	AHuman* HumanOwner;

	/** . */
	UPROPERTY()
	UMeshComponent* Mesh;

	/** . */
	UPROPERTY()
	UShapeComponent* Collision;

	/** . */
	UPROPERTY()
	UProjectileMovement* Movement;
};
