// Find something better to copy.

#include "ExtropyGameMode.h"
#include "Ego.h"
#include "UObject/ConstructorHelpers.h"

AExtropyGameMode::AExtropyGameMode(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set default pawn class to our Blueprinted Human.
	static ConstructorHelpers::FClassFinder<APawn> HumanBP(TEXT("/Game/Blueprints/BP_Human"));

	if (HumanBP.Succeeded() && HumanBP.Class)
	{
		DefaultPawnClass = HumanBP.Class;
	}

	PlayerControllerClass = AEgo::StaticClass();
}
