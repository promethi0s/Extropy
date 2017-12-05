// Find something better to copy.

/*=============================================================================
Human.cpp: Implements the UHumanCombat class
=============================================================================*/

#include "Ego.h"
#include "Human.h"

//----------------------------------------------------------------------//
// AWeapon
//----------------------------------------------------------------------//

AEgo::AEgo(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Initialize defaults
	BaseYawRate = 45.0f;
	BasePitchRate = 45.0f;
	MaxTapTime = 0.2f;
}

void AEgo::SetPawn(APawn* InPawn)
{
	AController::SetPawn(InPawn);
	HumanPawn = Cast<AHuman>(InPawn);
}

void AEgo::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("Vertical", this, &AEgo::AddVerticalInput);
	InputComponent->BindAxis("Horizontal", this, &AEgo::AddHorizontalInput);
	InputComponent->BindAxis("Pitch", this, &APlayerController::AddPitchInput);
	InputComponent->BindAxis("Yaw", this, &APlayerController::AddYawInput);
	InputComponent->BindAxis("PitchRate", this, &AEgo::PitchAtRate);
	InputComponent->BindAxis("YawRate", this, &AEgo::YawAtRate);

	InputComponent->BindAction("Jump", IE_Pressed, this, &AEgo::JumpPressed);
	InputComponent->BindAction("Crouch", IE_Pressed, this, &AEgo::CrouchPressed);
	InputComponent->BindAction("Crouch", IE_Released, this, &AEgo::CrouchReleased);
	InputComponent->BindAction("Sprint", IE_Pressed, this, &AEgo::SprintPressed);
	InputComponent->BindAction("Sprint", IE_Released, this, &AEgo::SprintReleased);

	InputComponent->BindAction("WeaponLeft", IE_Pressed, this, &AEgo::WeaponLeftPressed);
	InputComponent->BindAction("WeaponLeft", IE_Released, this, &AEgo::WeaponLeftReleased);
	InputComponent->BindAction("WeaponRight", IE_Pressed, this, &AEgo::WeaponRightPressed);
	InputComponent->BindAction("WeaponRight", IE_Released, this, &AEgo::WeaponRightReleased);
	InputComponent->BindAction("Ability1", IE_Pressed, this, &AEgo::Ability1Pressed);
	InputComponent->BindAction("Ability1", IE_Released, this, &AEgo::Ability1Released);
	InputComponent->BindAction("Ability2", IE_Pressed, this, &AEgo::Ability2Pressed);
	InputComponent->BindAction("Ability2", IE_Released, this, &AEgo::Ability2Released);
	InputComponent->BindAction("Ability3", IE_Pressed, this, &AEgo::Ability3Pressed);
	InputComponent->BindAction("Ability3", IE_Released, this, &AEgo::Ability3Released);
	InputComponent->BindAction("Ability4", IE_Pressed, this, &AEgo::Ability4Pressed);
	InputComponent->BindAction("Ability4", IE_Released, this, &AEgo::Ability4Released);

	InputComponent->BindAction("Loadout1", IE_Pressed, this, &AEgo::Loadout1Pressed);
	InputComponent->BindAction("Loadout2", IE_Pressed, this, &AEgo::Loadout2Pressed);
	InputComponent->BindAction("Loadout3", IE_Pressed, this, &AEgo::Loadout3Pressed);
	InputComponent->BindAction("Loadout4", IE_Pressed, this, &AEgo::Loadout4Pressed);

	InputComponent->BindAction("Interact", IE_Pressed, this, &AEgo::Interact);

	// InputComponent->BindAction("Equip", IE_Pressed, this, &AEgo::Equip);
	// InputComponent->BindAction("View", IE_Pressed, this, &AEgo::View);
}

void AEgo::ProcessPlayerInput(const float DeltaTime, const bool bGamePaused)
{
	if (!InputEnabled()) 
	{
		return;
	}

	Super::ProcessPlayerInput(DeltaTime, bGamePaused);

	if (HumanPawn)
	{
		FVector2D MovementDirection(VerticalMovement, HorizontalMovement);
		HumanPawn->ProcessDeferredInputs(MovementDirection);
	}

	VerticalMovement = 0.f;
	HorizontalMovement = 0.f;
}

void AEgo::AddVerticalInput(float Value)
{
	if (Value != 0.0f && HumanPawn)
	{
		// Store value to calculate dodge direction.
		VerticalMovement = Value;

		// Find forward direction.
		const FRotator YawRotation(0, ControlRotation.Yaw, 0);
		const FVector ForwardDirection(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X));

		// Add resulting movement vector.
		HumanPawn->AddMovementInput(ForwardDirection, Value);
	}
}

void AEgo::AddHorizontalInput(float Value)
{
	if (Value != 0.0f && HumanPawn)
	{
		// Store value to calculate dodge direction.
		HorizontalMovement = Value;

		// Find right direction.
		const FRotator YawRotation(0, ControlRotation.Yaw, 0);
		const FVector RightDirection(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y));

		// Add resulting movement vector.
		HumanPawn->AddMovementInput(RightDirection, Value);
	}
}

void AEgo::PitchAtRate(float Rate)
{
	if (Rate != 0.0f)
	{
		AddPitchInput(Rate * BasePitchRate * GetWorld()->GetDeltaSeconds());
	}
}

void AEgo::YawAtRate(float Rate)
{
	if (Rate != 0.0f)
	{
		AddYawInput(Rate * BaseYawRate * GetWorld()->GetDeltaSeconds());
	}
}

void AEgo::JumpPressed()
{
	if (HumanPawn)
	{
		HumanPawn->Jump();
	}
}

void AEgo::CrouchPressed()
{
	if (HumanPawn)
	{
		HumanPawn->StartCrouch();
		RollPressTime = GetWorld()->GetTimeSeconds();
	}
}

void AEgo::CrouchReleased()
{
	if (HumanPawn)
	{
		HumanPawn->StopCrouch();

		if (GetWorld()->GetTimeSeconds() - RollPressTime < MaxTapTime)
		{
			HumanPawn->Roll();
		}
	}
}

void AEgo::SprintPressed()
{
	if (HumanPawn)
	{
		HumanPawn->StartSprint();
		DodgePressTime = GetWorld()->GetTimeSeconds();
	}
}

void AEgo::SprintReleased()
{
	if (HumanPawn)
	{
		HumanPawn->StopSprint();

		if (GetWorld()->GetTimeSeconds() - DodgePressTime < MaxTapTime)
		{
			HumanPawn->Dodge();
		}
	}
}

void AEgo::WeaponLeftPressed()
{
	if (HumanPawn)
	{
		HumanPawn->QueueWeaponInput(EActionType::EAT_WeaponLeft, true);
	}
}

void AEgo::WeaponLeftReleased()
{
	if (HumanPawn) 
	{
		HumanPawn->QueueWeaponInput(EActionType::EAT_WeaponLeft, false);
	}
}

void AEgo::WeaponRightPressed()
{
	if (HumanPawn)
	{
		HumanPawn->QueueWeaponInput(EActionType::EAT_WeaponRight, true);
	}
}

void AEgo::WeaponRightReleased()
{
	if (HumanPawn) 
	{
		HumanPawn->QueueWeaponInput(EActionType::EAT_WeaponRight, false);
	}
}

void AEgo::Ability1Pressed()
{
	if (HumanPawn) 
	{
		HumanPawn->QueueWeaponInput(EActionType::EAT_Ability1, true);
	}
}

void AEgo::Ability1Released()
{
	if (HumanPawn) 
	{
		HumanPawn->QueueWeaponInput(EActionType::EAT_Ability1, false);
	}
}

void AEgo::Ability2Pressed()
{
	if (HumanPawn) 
	{
		HumanPawn->QueueWeaponInput(EActionType::EAT_Ability2, true);
	}
}

void AEgo::Ability2Released()
{
	if (HumanPawn) 
	{
		HumanPawn->QueueWeaponInput(EActionType::EAT_Ability2, false);
	}
}

void AEgo::Ability3Pressed()
{
	if (HumanPawn)
	{ 
		HumanPawn->QueueWeaponInput(EActionType::EAT_Ability3, true);
	}
}

void AEgo::Ability3Released()
{
	if (HumanPawn)
	{ 
		HumanPawn->QueueWeaponInput(EActionType::EAT_Ability3, false);
	}
}

void AEgo::Ability4Pressed()
{
	if (HumanPawn) 
	{
		HumanPawn->QueueWeaponInput(EActionType::EAT_Ability4, true);
	}
}

void AEgo::Ability4Released()
{
	if (HumanPawn)
	{
		HumanPawn->QueueWeaponInput(EActionType::EAT_Ability4, false);
	}
}

void AEgo::Loadout1Pressed()
{
	if (HumanPawn)
	{
		HumanPawn->UseWeaponLoadout(0);
	}
}

void AEgo::Loadout2Pressed()
{
	if (HumanPawn)
	{
		HumanPawn->UseWeaponLoadout(1);
	}
}

void AEgo::Loadout3Pressed()
{
	if (HumanPawn)
	{
		HumanPawn->UseWeaponLoadout(2);
	}
}

void AEgo::Loadout4Pressed()
{
	if (HumanPawn)
	{
		HumanPawn->UseWeaponLoadout(3);
	}
}

void AEgo::Interact()
{
	if (HumanPawn)
	{
		HumanPawn->Interact();
	}
}
