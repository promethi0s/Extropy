// Find something better to copy.

#include "AnimNotify_StartWindow.h"
#include "Human.h"

void UAnimNotify_StartWindow::Notify(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation)
{
	AHuman* HumanOwner = Cast<AHuman>(MeshComp->GetOwner());

	if (HumanOwner)
	{
		HumanOwner->StartDecisionWindow(Triggers, DefaultSection);
	}
}
