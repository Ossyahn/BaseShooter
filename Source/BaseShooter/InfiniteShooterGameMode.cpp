// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "InfiniteShooterGameMode.h"
#include "InfiniteShooterHUD.h"
#include "Player/FirstPersonCharacter.h"
#include "UObject/ConstructorHelpers.h"

AInfiniteShooterGameMode::AInfiniteShooterGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/BaseShooter/Characters/Common/BP_Character"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AInfiniteShooterHUD::StaticClass();
}
