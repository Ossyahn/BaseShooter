// Copyright 2020 Alberto Romero Garcia, all rights reserved.


#include "InfiniteMapGameMode.h"
#include "EngineUtils.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "../ActorPool/ActorPool.h"

AInfiniteMapGameMode::AInfiniteMapGameMode()
{
	NavMeshPool = CreateDefaultSubobject<UActorPool>(FName("NavMeshPool"));
}

void AInfiniteMapGameMode::PopulateBoundsVolumePool()
{
	auto ActorIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());
	while (ActorIterator)
	{
		ANavMeshBoundsVolume* FoundActor = *ActorIterator;
		AddToPool((ANavMeshBoundsVolume*)FoundActor);
		++ActorIterator;
	}
}

void AInfiniteMapGameMode::AddToPool(ANavMeshBoundsVolume* NavMesh)
{
	UE_LOG(LogTemp, Warning, TEXT("Found NavMesh: %s"), *NavMesh->GetName());
}
