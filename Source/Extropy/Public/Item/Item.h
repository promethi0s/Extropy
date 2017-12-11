// Find something better to copy.						

/*=============================================================================
Item.h: Implements the AItem class
=============================================================================*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

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
	virtual void Added(AHuman* NewOwner);

	/** . */
	UFUNCTION()
	virtual void Removed();

	/** . */
	UFUNCTION()
	void AttachMesh(FName Socket);

	/** . */
	UFUNCTION()
	void DetachMesh();

	/** . */
	UFUNCTION()
	AHuman* GetHumanOwner();

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
	class AHuman* HumanOwner;

	/** . */
	UPROPERTY()
	class UMeshComponent* Mesh;

	/** . */
	UPROPERTY()
	class UShapeComponent* Collision;

	/** . */
	UPROPERTY()
	class UProjectileMovement* Movement;

	//--------------------------------
	// Overrids
	//--------------------------------

public:

	virtual void Destroyed() override;
};
