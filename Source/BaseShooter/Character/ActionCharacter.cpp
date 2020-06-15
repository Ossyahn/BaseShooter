// Copyright 2020 Alberto Romero Garcia, all rights reserved.


#include "ActionCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "../Weapons/Gun.h"

// Sets default values
AActionCharacter::AActionCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.f);
		
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->SetupAttachment(FirstPersonCameraComponent);
	FirstPersonMesh->bCastDynamicShadow = false;
	FirstPersonMesh->CastShadow = false;
	
	auto ThirdPersonMesh = GetMesh();

	ThirdPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ThirdPersonMesh"));
	ThirdPersonMesh->SetOwnerNoSee(true);
	ThirdPersonMesh->SetupAttachment(GetCapsuleComponent());
}

// Called when the game starts or when spawned
void AActionCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (GunBlueprint) {
		Gun = GetWorld()->SpawnActor<AGun>(GunBlueprint);
		Gun->AttachToComponent(FirstPersonMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
		Gun->AnimInstance = FirstPersonMesh->GetAnimInstance();
	}
	
}
