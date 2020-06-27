// Copyright 2020 Alberto Romero Garcia, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ActionCharacter.generated.h"

class AGun;
class UHealthComponent;
class UCameraComponent;
class USkeletalMeshComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FActionCharacterDelegate);


UCLASS()
class BASESHOOTER_API AActionCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UArrowComponent* DeathCameraSpawnPoint;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "Mesh")
	USkeletalMeshComponent* FirstPersonMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = "true"))
	UHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, Category = "DeathCam")
	float BlendTime = 3.f;

	UPROPERTY(EditDefaultsOnly, Category = "DeathCam")
	TEnumAsByte<EViewTargetBlendFunction> BlendFunction = EViewTargetBlendFunction::VTBlend_EaseOut;

	UPROPERTY(EditDefaultsOnly, Category = "DeathCam")
	float BlendExponent = 5.f;

	UPROPERTY(EditDefaultsOnly, Category = "DeathCam")
	bool LockOutgoing = false;
	
public:
	// Sets default values for this character's properties
	AActionCharacter();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void PullTrigger();
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AGun> GunBlueprint;

	UPROPERTY(BlueprintAssignable, Category = "Death")
	FActionCharacterDelegate OnCharacterDeath;

	virtual void UnPossessed() override;
	virtual void PossessedBy(AController* NewController) override;
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

	UFUNCTION()
	void OnDeath();
};
