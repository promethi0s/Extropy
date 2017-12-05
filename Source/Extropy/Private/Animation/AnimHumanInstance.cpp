// Find something better to copy.

#include "AnimHumanInstance.h"

UAnimMontage* UAnimHumanInstance::GetWeaponMontage() const
{
	return WeaponMontage && Montage_IsPlaying(WeaponMontage) ? WeaponMontage : nullptr;
}

void UAnimHumanInstance::SetWeaponMontage(UAnimMontage* NewMontage)
{
	WeaponMontage = NewMontage;

	if (WeaponMontage)
	{
		Montage_Play(WeaponMontage);
	}
}

void UAnimHumanInstance::SetWeaponSection(FName NewSection)
{
	if (WeaponMontage)
	{
		Montage_JumpToSection(NewSection, WeaponMontage);
	}
}

void UAnimHumanInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	// HumanOwner = Cast<AExtropyCharacter>(TryGetPawnOwner());
}

void UAnimHumanInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
}
