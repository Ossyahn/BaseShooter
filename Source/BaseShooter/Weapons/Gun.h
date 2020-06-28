// Copyright 2020 Alberto Romero Garcia, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class BASESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* SkeletalMesh;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* MuzzleComponent;
		

public:
	AGun();
	
	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AProjectile> ProjectileClass;

	/** Alignment of the center of the reticule in screen size proportion (0.5 is middle) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reticule")
	FVector2D ReticuleCenterScreenAlignment = FVector2D(0.5f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reticule")
		float TraceDistance = 10000.f;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	class UAnimMontage* FirstPersonFireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	class UAnimMontage* ThirdPersonFireAnimation;

	/* AnimInstance of whatever holds the gun to be animated when firing*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	class UAnimInstance* FirstPersonAnimInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	class UAnimInstance* ThirdPersonAnimInstance;

	/** Fires a projectile. */
	UFUNCTION(BlueprintCallable)
	void Fire(FVector TargetLocation);
	
private:
	void SpawnProjectile();
	
	FVector TargetLocation;
};
