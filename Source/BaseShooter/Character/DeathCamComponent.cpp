// Copyright 2020 Alberto Romero Garcia, all rights reserved.


#include "DeathCamComponent.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraActor.h"
#include "Camera/PlayerCameraManager.h"

UDeathCamComponent::UDeathCamComponent()
{
	ArrowColor = FColor::Blue;
	bHiddenInGame = true;
}

void UDeathCamComponent::ExecuteDeathCam(APlayerController* PlayerController)
{
	if (!PlayerController) return;
	
	auto DeathCamera = GetWorld()->SpawnActor<ACameraActor>(
		GetComponentLocation(),
		GetComponentRotation()
	);

	PlayerController->SetViewTargetWithBlend(
		DeathCamera, BlendTime, BlendFunction, BlendExponent);	
}
