// Find something better to copy.

/*=============================================================================
Item.cpp: Implements the AItem class
=============================================================================*/

#include "Item.h"
#include "Human.h"

#include "Components/MeshComponent.h"

//----------------------------------------------------------------------//
// AItem
//----------------------------------------------------------------------//

void AItem::Added(AHuman* NewOwner)
{
	Instigator = NewOwner;
	SetOwner(NewOwner);
	HumanOwner = NewOwner;
	PrimaryActorTick.AddPrerequisite(HumanOwner, HumanOwner->PrimaryActorTick);
}

void AItem::Removed()
{
	if (HumanOwner)
	{
		PrimaryActorTick.RemovePrerequisite(HumanOwner, HumanOwner->PrimaryActorTick);
	}

	Instigator = nullptr;
	SetOwner(nullptr);
	HumanOwner = nullptr;
}

void AItem::AttachMesh(FName Socket)
{
	if (Mesh)
	{
		USkeletalMeshComponent* HumanMesh = HumanOwner ? HumanOwner->GetMesh() : nullptr;

		Mesh->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
		Mesh->AttachToComponent(HumanMesh, FAttachmentTransformRules::KeepRelativeTransform, Socket);
	}
}

void AItem::DetachMesh()
{
	if (Mesh)
	{
		Mesh->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	}
}

AHuman* AItem::GetHumanOwner()
{
	return HumanOwner;
}

void AItem::Destroyed()
{
	if (HumanOwner != NULL)
	{
		// HumanOwner->RemoveItem(this);
	}

	GetWorldTimerManager().ClearAllTimersForObject(this);

	Super::Destroyed();
}
