// Copyright 2020 Alberto Romero Garcia, all rights reserved.


#include "ActorPool.h"

// Sets default values for this component's properties

AActor* UActorPool::Acquire()
{
	AActor* ActorToReturn = Actor;
	Actor = nullptr;
	return ActorToReturn;
}

void UActorPool::Release(AActor* InActor)
{
	Actor = InActor;
}

void UActorPool::Add(AActor* InActor)
{
	Release(InActor);
}

