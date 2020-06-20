// Copyright 2020 Alberto Romero Garcia, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "InfiniteMapGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BASESHOOTER_API AInfiniteMapGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AInfiniteMapGameMode();

	UFUNCTION(BlueprintCallable, Category = Pooling)
	void PopulateBoundsVolumePool();
		
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "NavMeshPool")
	class UActorPool* NavMeshPool;	

private:
	void AddToPool(class ANavMeshBoundsVolume* NavMesh);
	
};
