// Find something better to copy.
/*
//----------------------------------------------------------------------//
// UInventory
//----------------------------------------------------------------------//

void UInventory::Add(AExtropyItem* Item)
{
	if (!Item)
	{
		return;
	}

	const int32 Index = FindSlot(Item);

	// Cannot hold multiple unique items.
	if (Index > -1 && Item->IsUnique())
	{
		return;
	}
	

	if (Index == -1)
	{
		Items.Add(FInventorySlot(Item));
	}
	else
	{
		Items[Index].Count++;
	}
}

void UInventory::LocalAdd(AExtropyItem* Item)
{
}

void UInventory::ClientAdd_Implementation(AExtropyItem* Item)
{
}

void UInventory::ServerAdd_Implementation(AExtropyItem* Item)
{
}

bool UInventory::ServerAdd_Validate(AExtropyItem* Item)
{
	// !TODO Should check weapons exist and are in inventory, and character is currently free to switch
	return true;
}

void UInventory::Remove(AExtropyItem* Item)
{
	int32 Index = FindSlot(Item);

	if (Index == -1)
	{
		// Item not in inventory.
		return;
	}

	FInventorySlot Slot = Items[Index];
	
	if (Slot.Count == 1)
	{
		Items.RemoveAt(Index);
	}
	else
	{
		Slot.Count--;
	}
}

void UInventory::LocalRemove(AExtropyItem* Item)
{
}

void UInventory::ClientRemove_Implementation(AExtropyItem* Item)
{
}

void UInventory::ServerRemove_Implementation(AExtropyItem* Item)
{
}

bool UInventory::ServerRemove_Validate(AExtropyItem* Item)
{
	// !TODO Should check weapons exist and are in inventory, and character is currently free to switch
	return true;
}

int32 UInventory::FindSlot(AExtropyItem* Item) const
{
	for (int32 i = 0; i < Items.Num(); i++)
	{
		if (Items[i].Item == Item)
		{
			return i;
		}
	}

	return -1;
}

//----------------------------------------------------------------------//
// FWeaponLoadout
//----------------------------------------------------------------------//

void FWeaponLoadout::SetLeft(class AWeapon* Weapon)
{
if (!Weapon)
{
Left = Weapon;
return;
}

if (Right && Right->GetGrip() == EWeaponGrip::GRIP_Both)
{
Right = nullptr;
}

switch (Weapon->GetGrip())
{
case EWeaponGrip::GRIP_Either:
case EWeaponGrip::GRIP_Left:
Left = Weapon;
break;
case EWeaponGrip::GRIP_Both:
Right = Weapon;
default:
Left = nullptr;
}
}

void FWeaponLoadout::SetRight(class AWeapon* Weapon)
{
if (!Weapon)
{
Right = Weapon;
return;
}

switch (Weapon->GetGrip())
{
case EWeaponGrip::GRIP_Both:
Left = nullptr;
case EWeaponGrip::GRIP_Either:
case EWeaponGrip::GRIP_Right:
Right = Weapon;
break;
default:
Right = nullptr;
}
}

AWeapon::AWeapon(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
}

UStaticMesh* AWeapon::GetMesh() const
{
return nullptr;
}
*/
