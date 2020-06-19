// Copyright 2020 Alberto Romero Garcia, all rights reserved.


#include "InfiniteMapGameMode.h"
#include "EngineUtils.h"
#include "NavMesh/NavMeshBoundsVolume.h"

void AInfiniteMapGameMode::PopulateBoundsVolumePool()
{
	auto ActorIterator = TActorIterator<AActor>(GetWorld());
	while (ActorIterator)
	{
		AActor* FoundActor = *ActorIterator;
		if (FoundActor->IsA(AActor::StaticClass()))
		{
			AddToPool(FoundActor);
		}
		++ActorIterator;
	}
}

void AInfiniteMapGameMode::AddToPool(AActor* NavMesh)
{
	//UE_LOG(LogTemp, Warning, TEXT("Found NavMesh: %s"), *NavMesh->GetName());
}
