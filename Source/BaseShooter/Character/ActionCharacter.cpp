// Copyright 2020 Alberto Romero Garcia, all rights reserved.


#include "ActionCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "../Weapons/Gun.h"
#include "HealthComponent.h"

// Sets default values
AActionCharacter::AActionCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.f);
		
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(FName("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(0.45f,1.75f, 64.f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("FirstPersonMesh"));
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->SetupAttachment(FirstPersonCameraComponent);
	FirstPersonMesh->bCastDynamicShadow = false;
	FirstPersonMesh->CastShadow = false;
	FirstPersonMesh->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));
	
	USkeletalMeshComponent* ThirdPersonMesh = GetMesh();
		
	ThirdPersonMesh->SetOwnerNoSee(true);
	ThirdPersonMesh->SetupAttachment(GetCapsuleComponent());	

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(FName("Health"));
}

void AActionCharacter::PullTrigger()
{
	if (Gun) {
		Gun->Fire();
	}
}

// Called when the game starts or when spawned
void AActionCharacter::BeginPlay()
{
	Super::BeginPlay();

	//HealthComponent->OnDeath.AddDynamic(this, &AActionCharacter::OnDeath);

	//TODO: have weapon previously spawned instead that on begin play
	if (!GunBlueprint) return;

	Gun = GetWorld()->SpawnActor<AGun>(GunBlueprint);

	if (IsPlayerControlled()) 
	{
		Gun->AttachToComponent(FirstPersonMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), FName("GripPoint"));
	}
	else 
	{
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), FName("GripPoint"));

	}

	Gun->FirstPersonAnimInstance = FirstPersonMesh->GetAnimInstance();
	Gun->ThirdPersonAnimInstance = GetMesh()->GetAnimInstance();
		
}

void AActionCharacter::OnDeath()
{
	OnCharacterDeath.Broadcast();
}

void AActionCharacter::UnPossessed()
{
	Super::UnPossessed();

	if (!Gun) return;

	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), FName("GripPoint"));
}

void AActionCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AActionCharacter::PullTrigger);	
}
