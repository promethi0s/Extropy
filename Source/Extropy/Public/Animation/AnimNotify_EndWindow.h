// Find something better to copy.

#pragma once

#include "Extropy.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_EndWindow.generated.h"

/**
 * 
 */
UCLASS()
class EXTROPY_API UAnimNotify_EndWindow : public UAnimNotify
{
	GENERATED_BODY()

	// Begin UAnimNotify interface
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	// End UAnimNotify interface
};
