// Find something better to copy.

#pragma once

#include "Extropy.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "ExtropyTypes.h"
#include "AnimNotify_StartWindow.generated.h"

/**
 * 
 */
UCLASS()
class EXTROPY_API UAnimNotify_StartWindow : public UAnimNotify
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TArray<FActionTrigger> Triggers;

	UPROPERTY()
	FName DefaultSection;

	// Begin UAnimNotify interface
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	// End UAnimNotify interface
};
