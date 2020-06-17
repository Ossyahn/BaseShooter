// Copyright 2020 Alberto Romero Garcia, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapTile.generated.h"

class UBoxComponent;

UCLASS()
class BASESHOOTER_API AMapTile : public AActor
{
	GENERATED_BODY()

	// Box area on which actors will spawn procedurally in this Map Tile
	UPROPERTY(VisibleDefaultsOnly)
	UBoxComponent* SpawnBox = nullptr;
	
public:	
	// Sets default values for this actor's properties
	AMapTile();

	UFUNCTION(BlueprintCallable, Category = Map)
	void SpawnActors(TSubclassOf<AActor> ToSpawn, int MinAmount, int MaxAmount);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
