// Copyright 2020 Alberto Romero Garcia, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "PatrollingGuard.generated.h"

/**
 * 
 */
UCLASS()
class INFINITESHOOTER_API APatrollingGuard : public ATP_ThirdPersonCharacter
{
	GENERATED_BODY()
		
public:
	UPROPERTY(EditInstanceOnly, Category = "Patrol")
	TArray<AActor*> Waypoints;
	
};
