// Find something better to copy.

/*=============================================================================
Projectile.h: Implements the AProjectile class
=============================================================================*/

#pragma once

#include "Extropy.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UMeshComponent;
class UCapsuleComponent;
class UProjectileMovement;

/**
* Base class for all items able to be picked up by player.
* @see AWeapon, AArmor, AQuestItem, AConsumable, AAmmo
*/
UCLASS()
class EXTROPY_API AProjectile : public AActor
{
	GENERATED_UCLASS_BODY()
	
	UMeshComponent* Mesh;
	UCapsuleComponent* Collision;
	UProjectileMovement* Movement;

	void InitializeMovement(const FVector& StartPosition, const FVector& StartVelocity, const float MaximumOffset);
};
