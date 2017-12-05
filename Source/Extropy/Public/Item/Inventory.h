// Find something better to copy.

/*=============================================================================
Item.h: Implements the AItem class
=============================================================================*/

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Item.generated.h"

/**
* Base class for all items able to be picked up by player.
* @see AWeapon, AArmor, AQuestItem, AConsumable, AAmmo
*/
UCLASS()
class EXTROPY_API UInventory : public UActorComponent
{
	GENERATED_BODY()
};
