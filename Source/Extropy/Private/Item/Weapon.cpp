// Find something better to copy.

/*=============================================================================
	Weapon.cpp: Implements the AWeapon class
=============================================================================*/

#include "Weapon.h"
#include "Human.h"

#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"

//----------------------------------------------------------------------//
// AWeapon
//----------------------------------------------------------------------//

EGripType AWeapon::GetGrip() const
{
	return Grip;
}

EWeaponType AWeapon::GetType() const
{
	return Type;
}

void AWeapon::Arm()
{
	AttachMesh(WeaponSocket);
}

void AWeapon::Disarm()
{
	AttachMesh(DefaultSocket);
}
