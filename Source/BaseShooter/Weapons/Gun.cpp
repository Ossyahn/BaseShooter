// Copyright 2020 Alberto Romero Garcia, all rights reserved.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"
#include "TimerManager.h"


// Sets default values
AGun::AGun() 
{
	// Create a gun mesh component
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SkeletalMesh->SetOnlyOwnerSee(false);			
	SkeletalMesh->bCastDynamicShadow = false;
	SkeletalMesh->CastShadow = false;
	SkeletalMesh->SetupAttachment(RootComponent);

	RootComponent = SkeletalMesh;

	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	MuzzleLocation->SetupAttachment(SkeletalMesh);
	MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));	
}

void AGun::Fire()
{

	if (!ProjectileClass) return;
	
	// try and play the sound if specified
	if (FireSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// try and play a firing animation if specified
	if (FirstPersonFireAnimation != NULL && FirstPersonAnimInstance != NULL)
	{		
		FirstPersonAnimInstance->Montage_Play(FirstPersonFireAnimation, 1.f);		
	}

	if (ThirdPersonFireAnimation != NULL && ThirdPersonAnimInstance != NULL)
	{
		ThirdPersonAnimInstance->Montage_Play(ThirdPersonFireAnimation, 1.f);
	}

	// Delay to allow the animation system to reset before spawning next shot
	FTimerHandle Handle;
	GetWorldTimerManager().SetTimer(Handle, this, &AGun::SpawnProjectile, 0.01f, false);
}

void AGun::SpawnProjectile()
{
	UWorld* const World = GetWorld();
	if (World != NULL)
	{
		const FRotator SpawnRotation = MuzzleLocation->GetComponentRotation();
		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
		const FVector SpawnLocation = MuzzleLocation->GetComponentLocation();

		// Set Spawn Collision Handling Override
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		// TODO: Fix collision with player own capsule 
		// Spawn the projectile at the muzzle
		World->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
	}
}

