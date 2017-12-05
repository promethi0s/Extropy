// Find something better to copy.

/*=============================================================================
Projectile.cpp: Implements the AProjectile class
=============================================================================*/

#include "Projectile.h"

#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"

//----------------------------------------------------------------------//
// AProjectile
//----------------------------------------------------------------------//

AProjectile::AProjectile(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	Mesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("MissileMesh"));
	// Mesh->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::OnlyTickPoseWhenRendered;
	Mesh->bReceivesDecals = false;
	Mesh->CastShadow = true;
	Mesh->SetCollisionObjectType(ECC_WorldDynamic);
	Mesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	Mesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	Mesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	Mesh->SetCollisionResponseToChannel(COLLISION_PICKUP, ECR_Block);
	Mesh->SetCollisionResponseToChannel(COLLISION_WEAPON, ECR_Block);
	Mesh->SetCollisionResponseToChannel(COLLISION_PROJECTILE, ECR_Block);
	RootComponent = Mesh;
}

void AProjectile::InitializeMovement(const FVector& StartPosition, const FVector& StartVelocity, const float MaximumOffset)
{
	if (Collision)
	{
		FHitResult Hit;
		GetWorld()->SweepSingleByChannel(
			Hit,
			StartPosition - FVector(StartVelocity.X, StartVelocity.Y, 0.0f) * MaximumOffset,
			StartPosition,
			FQuat::Identity,
			Collision->GetCollisionObjectType(),
			Collision->GetCollisionShape(),
			FCollisionQueryParams(FName(TEXT("SpawnCheck"))),
			Collision->GetCollisionResponseToChannels()
		);

		if (Hit.bBlockingHit && !Hit.bStartPenetrating)
		{
			// Check spawn location for blocking geometry.
			SetActorLocation(Hit.Location);
		}
	}
}
