// Copyright 2020 Alberto Romero Garcia, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorPool.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BASESHOOTER_API UActorPool : public UActorComponent
{
	GENERATED_BODY()

public:		
	AActor* Acquire();
	void Release(AActor* Actor);
	void Add(AActor* Actor);

private:
	AActor* Actor;
};
