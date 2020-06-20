// Copyright 2020 Alberto Romero Garcia, all rights reserved.


#include "ActorPool.h"

// Sets default values for this component's properties

AActor* UActorPool::Acquire()
{
	if (Pool.Num() == 0)
	{
		return nullptr;
	}
	return Pool.Pop();
}

void UActorPool::Release(AActor* InActor)
{
	Pool.Push(InActor);
}

void UActorPool::Add(AActor* InActor)
{
	Release(InActor);
}

