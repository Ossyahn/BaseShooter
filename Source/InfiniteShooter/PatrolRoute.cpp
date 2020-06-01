// Copyright 2020 Alberto Romero Garcia, all rights reserved.


#include "PatrolRoute.h"

// Sets default values for this component's properties
UPatrolRoute::UPatrolRoute()
{
}


TArray<AActor*> UPatrolRoute::GetWaypoints()
{
	return Waypoints;
}

// Called when the game starts
void UPatrolRoute::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


