// Copyright 2020 Alberto Romero Garcia, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapTile.generated.h"

class UBoxComponent;
class UHierarchicalInstancedStaticMeshComponent;

struct BoundsData
{
	FVector Origin;
	FVector Extent;
	float InnerRadius;
	float OuterRadius;
};

UENUM()
enum SpawnRotation
{
	None			UMETA(DisplayName = "None"),
	RandomAllAxis	UMETA(DisplayName = "Random All Axis"),
	RandomYaw		UMETA(DisplayName = "Random Yaw")
};

UCLASS()
class BASESHOOTER_API AMapTile : public AActor
{
	GENERATED_BODY()
			
public:	
	// Sets default values for this actor's properties
	AMapTile();

	// Spawns a number of actors between MinAmount and MaxAmount of the given class somewhere 
	// inside the SpawnBox. 
	UFUNCTION(BlueprintCallable, Category = Map)
	void SpawnActorsRandomly(TSubclassOf<AActor> ToSpawn, int MinAmount = 1, int MaxAmount = 1, TEnumAsByte<SpawnRotation> SpawnRotation = SpawnRotation::None, float MinScale = 1.f, float MaxScale = 1.f);

	UFUNCTION(BlueprintCallable, Category = Map)
	void SpawnGrassRandomly(UHierarchicalInstancedStaticMeshComponent* GrassInstancedComponent, UBoxComponent* SpawnArea, int32 NumInstances);
		
	UFUNCTION(BlueprintCallable, Category = "NavMesh")
	void SetNavMeshPool(class UActorPool* InNavMeshPool);

	// Box area on which actors will spawn procedurally in this Map Tile
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	UBoxComponent* SpawnBox = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Spawn)
	int32 MaxTries = 10;
	
	UPROPERTY(EditDefaultsOnly, Category = Spawn)
	bool bDrawDebugSpawnVolumes = false;

	

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	void PositionNavMesh();
	bool CastSphere(FVector Location, float Radius, bool bDebugDraw = false);
	bool GetEmptyRandomLocation(FVector BoundsCenter, float BoundRadius, FVector& OutRandomWorldLocation);
	BoundsData GetBoundsData(AActor* Actor, bool bDebugDraw = false);
	AActor* SpawnActor(TSubclassOf<AActor> ToSpawn, TEnumAsByte<SpawnRotation> SpawnRotation, float MinScale, float MaxScale);

	class UActorPool* NavMeshPool;
	class ANavMeshBoundsVolume* NavMesh;
};
