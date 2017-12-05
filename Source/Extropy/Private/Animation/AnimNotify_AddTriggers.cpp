// Find something better to copy.

#include "AnimNotify_AddTriggers.h"
#include "Human.h"

void UAnimNotify_AddTriggers::Notify(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation)
{
	AHuman* HumanOwner = Cast<AHuman>(MeshComp->GetOwner());

	if (HumanOwner)
	{
		HumanOwner->AddCombatTriggers(Triggers);
	}
}
