// Find something better to copy.

#include "AnimNotify_EndWindow.h"
#include "Human.h"

void UAnimNotify_EndWindow::Notify(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation)
{
	AHuman* HumanOwner = Cast<AHuman>(MeshComp->GetOwner());

	if (HumanOwner)
	{
		HumanOwner->EndDecisionWindow();
	}
}
