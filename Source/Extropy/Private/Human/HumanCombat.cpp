// Find something better to copy.

/*=============================================================================
HumanCombat.cpp: Implements the UHumanCombat class
=============================================================================*/

#include "HumanCombat.h"
#include "Human.h"
#include "AnimHumanInstance.h"
#include "Weapon.h"

//----------------------------------------------------------------------//
// UHumanCombat
//----------------------------------------------------------------------//

const FName UHumanCombat::DefaultSection = FName(TEXT("Default"));
const FName UHumanCombat::DisarmSection = FName(TEXT("Disarm"));

UHumanCombat::UHumanCombat(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Slots.Init(FWeaponSet(), 4);
}

void UHumanCombat::AssignSlot(AWeapon* Weapon, int32 Index, bool bOffHand)
{
	const EGripType WeaponGrip = Weapon ? Weapon->GetGrip() : EGripType::GRIP_None;
	
	switch (WeaponGrip)
	{
	case EGripType::GRIP_Left:
		Slots[Index].Left = Weapon;
		break;
	case EGripType::GRIP_Both:
		Slots[Index].Left = nullptr;
	case EGripType::GRIP_Right:
		Slots[Index].Right = Weapon;
		break;
	default:
		if (bOffHand)
		{
			Slots[Index].Left = Weapon;
		}
		else
		{
			Slots[Index].Right = Weapon;
		}
	}

	// Clear current in case no match found
	Slots[Index].Montage = FindMontage(Slots[Index]);
}

void UHumanCombat::UseSlot(int32 Index)
{
	if (ActiveSlot == -1)
	{
		// No weapon active; arm immediately
		PendingSlot = Index;
		SwitchWeapon();
	}
	else if (PendingSlot == -1)
	{
		// No pending weapon; disarm active
		PendingSlot = ActiveSlot = Index ? -1 : Index;
		NextSection = DisarmSection;
		EndWindow();
	}
	else
	{
		// Already disarming; update pending
		PendingSlot = PendingSlot = Index ? -1 : Index;		
	}
}

void UHumanCombat::QueueAction(EActionType Type, bool bPressed)
{
	if (bPressed)
	{
		Held.Add(Type);
		Presses.Add(Type);
	}
	else
	{
		Held.Remove(Type);
	}
}

void UHumanCombat::ProcessQueue(TArray<EActionModifier> MovementState)
{
	Modifiers = MovementState;

	for (auto& Trigger : Triggers)
	{
		if (ValidateTrigger(Trigger))
		{
			NextSection = Trigger.TargetSection;

			if (Trigger.bInterruptCurrent)
			{
				EndWindow();
			}
		}
	}
}

void UHumanCombat::StartWindow(TArray<FActionTrigger> NewTriggers, FName DefaultNextSection)
{
	Presses.Reset();

	Triggers = NewTriggers;
	NextSection = DefaultNextSection;
}

void UHumanCombat::AddTriggers(TArray<FActionTrigger> NewTriggers)
{
	Triggers.Append(NewTriggers);
}

void UHumanCombat::EndWindow()
{
	Triggers.Reset();

	if (AnimInstance && AnimMontage)
	{
		AnimInstance->Montage_JumpToSection(NextSection, AnimMontage);
		NextSection = DefaultSection;
	}
}

void UHumanCombat::Arm()
{
	if (Slots[ActiveSlot].Left)
	{
		Slots[ActiveSlot].Left->Arm();
	}

	if (Slots[ActiveSlot].Right)
	{
		Slots[ActiveSlot].Right->Arm();
	}
}

void UHumanCombat::Disarm()
{
	if (Slots[ActiveSlot].Left)
	{
		Slots[ActiveSlot].Left->Disarm();
	}

	if (Slots[ActiveSlot].Right)
	{
		Slots[ActiveSlot].Right->Disarm();
	}
}

void UHumanCombat::SwitchWeapon()
{
	Disarm();

	ActiveSlot = PendingSlot;
	PendingSlot = -1;

	if (Slots.IsValidIndex(ActiveSlot))
	{
		const AHuman* HumanOwner = Cast<AHuman>(GetOwner());
		const USkeletalMeshComponent* Mesh = HumanOwner ? HumanOwner->GetMesh() : nullptr;
		AnimInstance = Mesh ? Mesh->GetAnimInstance() : nullptr;
		AnimMontage = Slots[ActiveSlot].Montage;

		if (AnimInstance && AnimMontage)
		{
			AnimInstance->Montage_Play(AnimMontage);
		}
	}
}

UAnimMontage* UHumanCombat::FindMontage(const FWeaponSet& Weapon) const
{
	for (auto& Stance : WeaponStances)
	{
		const bool bLeftMatch = Weapon.Left ? Stance.LeftType == Weapon.Left->GetType() : Stance.LeftType == EWeaponType::WEAPON_None;
		const bool bRightMatch = Weapon.Right ? Stance.RightType == Weapon.Right->GetType() : Stance.RightType == EWeaponType::WEAPON_None;

		if (bLeftMatch && bRightMatch)
		{
			return Stance.Montage;
		}
	}

	return nullptr;
}

bool UHumanCombat::ValidateTrigger(const FActionTrigger& Trigger) const
{
	if (Trigger.State == EActionState::EAS_Released)
	{
		return !Held.Contains(Trigger.Type);
	}

	if (Trigger.State == EActionState::EAS_Held || Presses.Contains(Trigger.Type))
	{
		for (auto& Modifier : Trigger.RejectedModifiers)
		{
			if (Modifiers.Contains(Modifier)) { return false; }
		}

		for (auto& Modifier : Trigger.RequiredModifiers)
		{
			if (!Modifiers.Contains(Modifier)) { return false; }
		}

		return true;
	}

	return false;
}
