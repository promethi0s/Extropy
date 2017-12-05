// Find something better to copy.

#pragma once

#include "ExtropyTypes.generated.h"

/**
*
*/
UENUM(BlueprintType)
enum class EActionType : uint8
{
	EAT_WeaponLeft		UMETA(DisplayName = "Left Weapon"),
	EAT_WeaponRight		UMETA(DisplayName = "Right Weapon"),
	EAT_Ability1		UMETA(DisplayName = "Ability 1"),
	EAT_Ability2		UMETA(DisplayName = "Ability 2"),
	EAT_Ability3		UMETA(DisplayName = "Ability 3"),
	EAT_Ability4		UMETA(DisplayName = "Ability 4")
};

/**
*
*/
UENUM(BlueprintType)
enum class EActionState : uint8
{
	EAS_Pressed			UMETA(DisplayName = "Pressed"),
	EAS_Held			UMETA(DisplayName = "Held"),
	EAS_Released		UMETA(DisplayName = "Released")
};

/**
*
*/
UENUM(BlueprintType)
enum class EActionModifier : uint8
{
	EAM_MovingFwd		UMETA(DisplayName = "Moving Forward"),
	EAM_MovingBwd		UMETA(DisplayName = "Moving Backward"),
	EAM_MovingLeft		UMETA(DisplayName = "Moving Left"),
	EAM_MovingRight		UMETA(DisplayName = "Moving Right"),
	EAM_Crouching		UMETA(DisplayName = "Crouching"),
	EAM_Falling			UMETA(DisplayName = "Jumping"),
	EAM_Sprinting		UMETA(DisplayName = "Sprinting"),
	EAM_ParryLeft		UMETA(DisplayName = "Left Parry Opportunity"),
	EAM_ParryRight		UMETA(DisplayName = "Right Parry Opportunity")
};

/**
*
*/
UENUM(BlueprintType)
enum class EGripType : uint8
{
	GRIP_None			UMETA(DisplayName = "Default"),
	GRIP_Left			UMETA(DisplayName = "Left Handed"),
	GRIP_Right			UMETA(DisplayName = "Right Handed"),
	GRIP_Either			UMETA(DisplayName = "Left or Right Handed"),
	GRIP_Both			UMETA(DisplayName = "Two Handed")
};

/**
*
*/
UENUM(BlueprintType)
enum class EItemType : uint8
{
	ITEM_None			UMETA(DisplayName = "None"),
	ITEM_Armor			UMETA(DisplayName = "Armor"),
	ITEM_Weapon			UMETA(DisplayName = "Weapon")
};

/**
*
*/
UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	WEAPON_None			UMETA(DisplayName = "None"),
	WEAPON_Magic		UMETA(DisplayName = "Focusing Crystal"),
	WEAPON_Longbow		UMETA(DisplayName = "Longbow"),
	WEAPON_Shield		UMETA(DisplayName = "Shield"),
	WEAPON_Sword1H		UMETA(DisplayName = "One Handed Sword"),
	WEAPON_Sword2H		UMETA(DisplayName = "Two Handed Sword")
};

/**
*
*/
UENUM(BlueprintType)
enum class EWeaponStance : uint8
{
	STANCE_None			UMETA(DisplayName = "None/None"),
	STANCE_SwordLH		UMETA(DisplayName = "Sword1H/None"),
	STANCE_SwordRH		UMETA(DisplayName = "None/Sword1H"),
	STANCE_SwordDW		UMETA(DisplayName = "Sword1H/Sword1H"),
	STANCE_Shield		UMETA(DisplayName = "Shield/None"),
	STANCE_SwordShield	UMETA(DisplayName = "Shield/Sword1H"),
	STANCE_Sword2H		UMETA(DisplayName = "None/Sword2H"),
	STANCE_Longbow		UMETA(DisplayName = "None/Longbow")
};

/**
*
*/
UENUM(BlueprintType)
enum class EDamageSeverity : uint8
{
	EDS_None,
	EDS_Mild,
	EDS_Severe,
	EDS_Debilitating
};

USTRUCT(BlueprintType)
struct FActionTrigger
{
	GENERATED_BODY()

public:

	FActionTrigger()
	{}

	/**  */
	UPROPERTY(BlueprintReadWrite, Category = "CombatTrigger", EditAnywhere)
	EActionType Type;

	/** If true, trigger will be activated by release action and will disregard any modifiers. */
	UPROPERTY(BlueprintReadWrite, Category = "CombatTrigger", EditAnywhere)
	EActionState State;

	/**  */
	UPROPERTY(BlueprintReadWrite, Category = "CombatTrigger", EditAnywhere)
	TArray<EActionModifier> RequiredModifiers;

	/**  */
	UPROPERTY(BlueprintReadWrite, Category = "CombatTrigger", EditAnywhere)
	TArray<EActionModifier> RejectedModifiers;

	/**  */
	UPROPERTY(BlueprintReadWrite, Category = "CombatTrigger", EditAnywhere)
	FName TargetSection;

	/**  */
	UPROPERTY(BlueprintReadWrite, Category = "CombatTrigger", EditAnywhere)
	bool bInterruptCurrent;
};
