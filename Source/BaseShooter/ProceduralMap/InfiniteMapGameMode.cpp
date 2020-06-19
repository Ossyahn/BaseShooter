// Copyright 2020 Alberto Romero Garcia, all rights reserved.


#include "InfiniteMapGameMode.h"
#include "EngineUtils.h"

void AInfiniteMapGameMode::PopulateBoundsVolumePool()
{
	auto ActorIterator = TActorIterator<AActor>(GetWorld());
	while (ActorIterator)
	{
		AActor* FoundActor = *ActorIterator;
		AddToPool(FoundActor);
		++ActorIterator;
	}
}

void AInfiniteMapGameMode::AddToPool(AActor* Actor)
{
	UE_LOG(LogTemp, Warning, TEXT("Found Actor: %s"), *Actor->GetName());
}
