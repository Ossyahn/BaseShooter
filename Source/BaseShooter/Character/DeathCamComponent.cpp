// Copyright 2020 Alberto Romero Garcia, all rights reserved.


#include "DeathCamComponent.h"
#include "GameFramework/PlayerController.h"
#include "Camera/CameraActor.h"
#include "Camera/PlayerCameraManager.h"
#include "Math/Color.h"

UDeathCamComponent::UDeathCamComponent()
{
	ArrowColor = FColor().FromHex("3B66B5FF");
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
