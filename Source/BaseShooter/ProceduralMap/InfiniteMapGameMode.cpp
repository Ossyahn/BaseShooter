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

void AInfiniteMapGameMode::NewMapTileConquered()
{
	MapTilesConquered++;
	UE_LOG(LogTemp, Warning, TEXT("Map Tiles Conquered: %d"), MapTilesConquered);
}

void AInfiniteMapGameMode::AddToPool(ANavMeshBoundsVolume* NavMesh)
{
	NavMeshPool->Add(NavMesh);
}
