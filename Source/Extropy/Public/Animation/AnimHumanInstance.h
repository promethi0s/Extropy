// Find something better to copy.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ExtropyTypes.h"
#include "AnimHumanInstance.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class EXTROPY_API UAnimHumanInstance : public UAnimInstance
{
	GENERATED_BODY() 

public:

	UAnimMontage* GetWeaponMontage() const;
	void SetWeaponMontage(UAnimMontage* NewMontage);
	void SetWeaponSection(FName NewSection);

	void NativeInitializeAnimation() override;
	void NativeUpdateAnimation(float DeltaSeconds) override;

private:

	class AExtropyCharacter* HumanOwner;

	/** */
	UPROPERTY(Transient)
		class UAnimMontage* WeaponMontage;
};
