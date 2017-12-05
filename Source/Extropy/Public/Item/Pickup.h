// Find something better to copy.

/*=============================================================================
Pickup.h: Implements the APickup class
=============================================================================*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

class UMeshComponent;
class UShapeComponent;
class UProjectileMovement;

/**
* Base class for all items able to be picked up by player.
* @see AWeapon, AArmor, AQuestItem, AConsumable, AAmmo
*/
UCLASS()
class EXTROPY_API APickup : public AActor
{
	GENERATED_BODY()

	/** . */
	UPROPERTY()
	UMeshComponent* Mesh;

	/** . */
	UPROPERTY()
	UShapeComponent* Collision;
};
