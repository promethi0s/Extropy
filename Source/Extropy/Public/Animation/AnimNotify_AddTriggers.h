// Find something better to copy.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "ExtropyTypes.h"
#include "AnimNotify_AddTriggers.generated.h"

/**
 * 
 */
UCLASS()
class EXTROPY_API UAnimNotify_AddTriggers : public UAnimNotify
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TArray<FActionTrigger> Triggers;

	// Begin UAnimNotify interface
	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	// End UAnimNotify interface
};
