// Find something better to copy.

/*=============================================================================
Human.cpp: Implements the AHuman class
=============================================================================*/

#include "Human.h"
#include "HumanCombat.h"
#include "HumanMovement.h"
#include "Item.h"
#include "AnimHumanInstance.h"

#include "Animation/AnimBlueprint.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

//----------------------------------------------------------------------//
// AHuman
//----------------------------------------------------------------------//

AHuman::AHuman(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UHumanMovement>(CharacterMovementComponentName))
{
	// Get blueprint references
	static ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimBPRef(TEXT("AnimBlueprint'/Game/Blueprints/ABP_Human'"));
	if (AnimBPRef.Succeeded() && AnimBPRef.Object->GeneratedClass)
	{
		GetMesh()->SetAnimInstanceClass(AnimBPRef.Object->GeneratedClass);
	}

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(40.f, 108.0f);

	GetMesh()->bCastCapsuleIndirectShadow = true;
	GetMesh()->bEnablePhysicsOnDedicatedServer = true;
	GetMesh()->bLightAttachmentsAsGroup = true;
	GetMesh()->bReceivesDecals = false;
	GetMesh()->LightingChannels.bChannel1 = true;
	GetMesh()->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::OnlyTickPoseWhenRendered;
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Camera1P = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FirstPersonCamera"));
	Camera1P->SetupAttachment(GetCapsuleComponent());
	Camera1P->RelativeLocation = FVector(0, 0, BaseEyeHeight); // Position the camera
	Camera1P->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("FirstPersonMesh"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(Camera1P);
	Mesh1P->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::OnlyTickPoseWhenRendered;
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->bReceivesDecals = false;
	Mesh1P->PrimaryComponentTick.AddPrerequisite(this, PrimaryActorTick);
	Mesh1P->LightingChannels.bChannel1 = true;
	Mesh1P->bUseAttachParentBound = true;

	HumanMovement = Cast<UHumanMovement>(GetCharacterMovement());

	BaseEyeHeight = 83.f;
	CrouchedEyeHeight = 45.f;
}

void AHuman::StartCrouch()
{
	if (HumanMovement)
	{
		HumanMovement->SetCrouch(true);
	}
}

void AHuman::StopCrouch()
{
	if (HumanMovement)
	{
		HumanMovement->SetCrouch(false);
	}
}

void AHuman::StartSprint()
{
	if (HumanMovement)
	{
		HumanMovement->SetSprint(true);
	}
}

void AHuman::StopSprint()
{
	if (HumanMovement)
	{
		HumanMovement->SetSprint(false);
	}
}

void AHuman::Jump()
{
	if (HumanMovement)
	{
		HumanMovement->Jump();
	}
}

void AHuman::Dodge()
{
	bDodgeIntent = true;
}

void AHuman::Roll()
{
	bRollIntent = true;
}

void AHuman::StartDecisionWindow(TArray<FActionTrigger> NewTriggers, FName DefaultNextSection)
{
	if (HumanCombat)
	{
		HumanCombat->StartWindow(NewTriggers, DefaultNextSection);
	}
}

void AHuman::AddCombatTriggers(TArray<FActionTrigger> NewTriggers)
{
	if (HumanCombat)
	{
		HumanCombat->AddTriggers(NewTriggers);
	}
}

void AHuman::EndDecisionWindow()
{
	if (HumanCombat)
	{
		HumanCombat->EndWindow();
	}
}

void AHuman::DrawWeapon()
{
	// Assign attachments
}

void AHuman::HolsterWeapon()
{
	// Assign attachments
}

void AHuman::DisarmWeapon()
{
	if (HumanCombat)
	{
		HumanCombat->SwitchWeapon();
	}
}

void AHuman::QueueWeaponInput(EActionType Type, bool bPressed)
{
	if (HumanCombat)
	{
		HumanCombat->QueueAction(Type, bPressed);
	}
}

void AHuman::ProcessDeferredInputs(FVector2D MovementDirection)
{
	if (!HumanMovement)
	{
		return;
	}

	if (bDodgeIntent)
	{
		HumanMovement->Dodge(MovementDirection);
	}
	else if (bRollIntent)
	{
		HumanMovement->Roll(MovementDirection);
	}
	else if (HumanCombat)
	{
		TArray<EActionModifier> MovementState;

		if (MovementDirection.X > 0.1f) MovementState.Add(EActionModifier::EAM_MovingFwd);
		else if (MovementDirection.X < -0.1f) MovementState.Add(EActionModifier::EAM_MovingBwd);

		if (MovementDirection.Y > 0.1f) MovementState.Add(EActionModifier::EAM_MovingRight);
		else if (MovementDirection.Y < -0.1f) MovementState.Add(EActionModifier::EAM_MovingLeft);

		if (HumanMovement->IsCrouching()) MovementState.Add(EActionModifier::EAM_Crouching);
		if (HumanMovement->IsFalling()) MovementState.Add(EActionModifier::EAM_Falling);
		if (HumanMovement->IsSprinting()) MovementState.Add(EActionModifier::EAM_Sprinting);

		HumanCombat->ProcessQueue(MovementState);
	}

	bDodgeIntent = false;
	bRollIntent = false;
}

void AHuman::UseWeaponLoadout(int32 Index)
{
	if (HumanCombat)
	{
		HumanCombat->UseSlot(Index);
	}
}

void AHuman::Interact()
{
	// Perform trace for interact target

	// If item, pick it up
	// If pickup successful
	// HumanCombat->
}

/*
bool AHuman::ValidateLoadout(AWeaponSet* Loadout) const
{
	for (auto& Stance : WeaponStances)
	{
		if (Loadout->Left->GetType() == Stance.LeftType && Loadout->Right->GetType() == Stance.RightType)
		{
			Loadout->Montage = Stance.Montage;
			return true;
		}
	}

	return false;
}
*/

bool AHuman::AddToInventory(AItem* ItemToAdd, bool bAutoActivate)
{
	if (ItemToAdd) // && !ItemToAdd->IsPendingKillPending())
	{
		AHuman* ItemOwner = ItemToAdd->GetHumanOwner();
		if (ItemOwner && ItemOwner != this && ItemOwner->IsInInventory(ItemToAdd))
		{
			UE_LOG(Extropy, Warning, TEXT("AddInventory (%s): Item %s is already in %s's inventory!"), *GetName(), *ItemToAdd->GetName(), *ItemOwner->GetName());
		}
		else
		{
			// !TODO Assign item to slot

			ItemToAdd->Added(this);

			return true;
		}
	}

	return false;
}

bool AHuman::IsInInventory(const AItem* ItemToCheck) const
{
	return true;
}

void AHuman::RemoveFromInventory(AItem* ItemToRemove)
{
	if (ItemToRemove)
	{
		if (Inventory.Remove(ItemToRemove) > 0)
		{
			// If item is active or pending, update combat component

			ItemToRemove->Removed();
		}
	}
}

void AHuman::TossItem(AItem* ItemToToss, FVector ExtraVelocity)
{
	if (Role == ROLE_Authority)
	{
		if (!ItemToToss)
		{
			UE_LOG(Extropy, Warning, TEXT("TossItem(): Item is nullptr."));
		}
		else if (!IsInInventory(ItemToToss))
		{
			UE_LOG(Extropy, Warning, TEXT("TossItem(): %s is not in %s's inventory."), *ItemToToss->GetName(), *GetName());
		}
		else
		{
			const FVector SpawnOrigin = GetActorLocation() + GetActorRotation().Vector() * GetSimpleCollisionCylinderExtent().X;
			const FVector SpawnVelocity = GetVelocity() + GetActorRotation().RotateVector(ExtraVelocity + FVector(300.0f, 0.0f, 150.0f));
			// ItemToToss->Toss(SpawnOrigin, SpawnVelocity);
		}
	}
}

UAnimInstance* AHuman::GetAnimInstance() const
{
	USkeletalMeshComponent* Mesh = GetMesh();
	return Mesh ? Mesh->GetAnimInstance() : nullptr;
}

USkeletalMeshComponent* AHuman::GetMesh() const
{
	return IsFirstPerson() ? Mesh1P : ACharacter::GetMesh();
}

bool AHuman::IsFirstPerson() const
{
	return IsAlive() && Controller && Controller->IsLocalPlayerController();
}

bool AHuman::IsAlive() const
{
	return true;
}
