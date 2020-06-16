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

	//UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	//USkeletalMeshComponent* ThirdPersonMesh;
	
public:
	// Sets default values for this character's properties
	AActionCharacter();

	UFUNCTION(BlueprintCallable, Category = Weapon)
	void PullTrigger();

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AGun> GunBlueprint;

	virtual void UnPossessed() override;
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	FORCEINLINE USkeletalMeshComponent* GetFirstPersonMesh() const { return FirstPersonMesh; }
	FORCEINLINE USkeletalMeshComponent* GetThirdPersonMesh() const { return GetMesh(); }
	FORCEINLINE UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
	FORCEINLINE AGun* GetGun() const { return Gun; }

protected:
	virtual void BeginPlay() override;

private:
	AGun* Gun = nullptr;
	class ChildActorComponent* GunComponent = nullptr;
};
