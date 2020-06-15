// Copyright 2020 Alberto Romero Garcia, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ActionCharacter.generated.h"

class AGun;
class UCameraComponent;
class USkeletalMeshComponent;

UCLASS()
class BASESHOOTER_API AActionCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* FirstPersonMesh;
	

public:
	// Sets default values for this character's properties
	AActionCharacter();

	UPROPERTY(VisibleDefaultsOnly)
	TSubclassOf<AGun> GunBlueprint;

	FORCEINLINE USkeletalMeshComponent* GetFirstPersonMesh() const { return FirstPersonMesh; }
	FORCEINLINE USkeletalMeshComponent* GetThirdPersonMesh() const { return GetMesh(); }
	FORCEINLINE UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
	FORCEINLINE AGun* GetGun() const { return Gun; }

protected:
	virtual void BeginPlay() override;

private:
	AGun* Gun;
	class ChildActorComponent* GunComponent;
};
