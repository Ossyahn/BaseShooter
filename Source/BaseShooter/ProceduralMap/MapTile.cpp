// Copyright 2020 Alberto Romero Garcia, all rights reserved.


#include "MapTile.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"

// Sets default values
AMapTile::AMapTile()
{ 	
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
	SpawnBox->InitBoxExtent(FVector(4000.f, 4000.f, 1.f));
	SpawnBox->SetupAttachment(RootComponent);
}

void AMapTile::SpawnActors(TSubclassOf<AActor> ToSpawn, int MinAmount = 1, int MaxAmount = 1)
{
	FVector BoxCenter = SpawnBox->GetComponentLocation();
	FVector MinPoint = BoxCenter - SpawnBox->GetScaledBoxExtent();
	FVector MaxPoint = BoxCenter + SpawnBox->GetScaledBoxExtent();

	int Amount = FMath::RandRange(MinAmount, MaxAmount);

	for (int i = 0; i <= Amount; i++) 
	{
		FVector RandomPoint = FMath::RandPointInBox(FBox(MinPoint, MaxPoint));
		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ToSpawn, RandomPoint, FRotator());
		SpawnedActor->AttachToComponent(RootComponent, FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));
	}
}

// Called when the game starts or when spawned
void AMapTile::BeginPlay()
{
	Super::BeginPlay();
	
}

