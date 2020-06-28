// Copyright 2020 Alberto Romero Garcia, all rights reserved.


#include "ActionCharacter.h"
#include "Camera/CameraComponent.h"
#include "Camera/CameraActor.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "Components/ArrowComponent.h"
#include "../Weapons/Gun.h"
#include "HealthComponent.h"
#include "GameFramework/PlayerController.h"
#include "DeathCamComponent.h"
#include "AIController.h"

// Sets default values
AActionCharacter::AActionCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.f);
		
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(FName("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(0.45f,1.75f, 64.f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	DeathCam = CreateDefaultSubobject<UDeathCamComponent>(FName("DeathCam"));
	DeathCam->SetupAttachment(GetCapsuleComponent());
	DeathCam->SetRelativeLocation(FVector(-285.f, 0.f, 280.f));
	DeathCam->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("FirstPersonMesh"));
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->SetupAttachment(FirstPersonCameraComponent);
	FirstPersonMesh->bCastDynamicShadow = false;
	FirstPersonMesh->CastShadow = false;
	FirstPersonMesh->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));
	
	USkeletalMeshComponent* ThirdPersonMesh = GetMesh();
		
	ThirdPersonMesh->SetOwnerNoSee(true);
	ThirdPersonMesh->SetupAttachment(GetCapsuleComponent());	

	GunChildActor = CreateDefaultSubobject<UChildActorComponent>(FName("Gun"));
	GunChildActor->SetupAttachment(ThirdPersonMesh, FName("GripPoint"));
		
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(FName("Health"));
}

void AActionCharacter::PullTrigger()
{
	if (!Gun) return;

	FVector TargetLocation;

	auto PlayerController = GetController<APlayerController>();
	if (PlayerController)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Player aim updated"));

		int32 ScreenSizeX;
		int32 ScreenSizeY;
		FVector AimOrigin;
		FVector AimDirection;

		FVector2D ReticuleAlignment = Gun->ReticuleCenterScreenAlignment;

		PlayerController->GetViewportSize(ScreenSizeX, ScreenSizeY);
		PlayerController->DeprojectScreenPositionToWorld(
			ScreenSizeX * ReticuleAlignment.X,
			ScreenSizeY * ReticuleAlignment.Y,
			AimOrigin,
			AimDirection
		);

		FHitResult Hit;
		FVector LineEnd = AimOrigin + (AimDirection * Gun->TraceDistance);

		bool bHit = GetWorld()->LineTraceSingleByChannel(
			Hit,
			AimOrigin,
			LineEnd,
			ECollisionChannel::ECC_Visibility
		);
		TargetLocation = bHit ? Hit.ImpactPoint : LineEnd;
	}
	else
	{
		auto AIController = GetController<AAIController>();
		if (!AIController) return;
		AActor* FocusActor = AIController->GetFocusActor();
		
		if (!FocusActor) return;
		TargetLocation = FocusActor->GetTargetLocation();
	}
	
	Gun->Fire(TargetLocation);	
}

void AActionCharacter::BeginPlay()
{
	Super::BeginPlay();

	InitGun();

	HealthComponent->OnNoHealth.AddDynamic(this, &AActionCharacter::OnDeath);
}

void AActionCharacter::OnDeath()
{
	OnCharacterDeath.Broadcast();
	
	if (!Controller) return;

	auto PlayerController = GetController<APlayerController>();
	DeathCam->ExecuteDeathCam(PlayerController);

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Controller->UnPossess();
}

void AActionCharacter::InitGun()
{
	Gun = Cast<AGun>(GunChildActor->GetChildActor());
	if (!Gun) return;
	
	Gun->FirstPersonAnimInstance = FirstPersonMesh->GetAnimInstance();
	Gun->ThirdPersonAnimInstance = GetMesh()->GetAnimInstance();	
}

void AActionCharacter::UnPossessed()
{
	Super::UnPossessed();
	
	GunChildActor->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), FName("GripPoint"));
}

void AActionCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	auto PlayerController = Cast<APlayerController>(NewController);

	if (PlayerController)
	{
		PlayerController->bAutoManageActiveCameraTarget = false;
		PlayerController->SetViewTarget(this);

		GunChildActor->AttachToComponent(FirstPersonMesh, 
			FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), 
			FName("GripPoint")
		);
	}
}

void AActionCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AActionCharacter::PullTrigger);	
}
