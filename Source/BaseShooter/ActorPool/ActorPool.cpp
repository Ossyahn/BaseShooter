// Copyright 2020 Alberto Romero Garcia, all rights reserved.


#include "ActorPool.h"

// Sets default values for this component's properties
UActorPool::UActorPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

AActor* UActorPool::Pull()
{
	UE_LOG(LogTemp, Warning, TEXT("[%s] Pool Pulled"), *(this->GetName()));

	return nullptr;
}

void UActorPool::Push(AActor* Actor)
{
}

void UActorPool::Add(AActor* Actor)
{
}
