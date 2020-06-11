// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "BaseShooterGameMode.h"
#include "BaseShooterHUD.h"
#include "Player/FirstPersonCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABaseShooterGameMode::ABaseShooterGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/BaseShooter/Characters/Common/BP_Character"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ABaseShooterHUD::StaticClass();
}
