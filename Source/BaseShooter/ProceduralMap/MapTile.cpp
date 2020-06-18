// Copyright 2020 Alberto Romero Garcia, all rights reserved.


#include "MapTile.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"

// Sets default values
AMapTile::AMapTile()
{ 	
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnBox"));
	SpawnBox->InitBoxExtent(FVector(4000.f, 4000.f, 1.f));
	SpawnBox->SetupAttachment(RootComponent);
}

void AMapTile::SpawnActorsRandomly(TSubclassOf<AActor> ToSpawn, int MinAmount = 1, int MaxAmount = 1)
{
	FVector BoxCenter = SpawnBox->GetRelativeLocation();
	FVector MinPoint = BoxCenter - SpawnBox->GetScaledBoxExtent();
	FVector MaxPoint = BoxCenter + SpawnBox->GetScaledBoxExtent();

	int Amount = FMath::RandRange(MinAmount, MaxAmount);

	for (int i = 0; i <= Amount; i++) 
	{
		FVector RandomPoint = FMath::RandPointInBox(FBox(MinPoint, MaxPoint));
		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ToSpawn, RandomPoint, FRotator());
		SpawnedActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
	}
}

// Called when the game starts or when spawned
void AMapTile::BeginPlay()
{
	Super::BeginPlay();

	CastSphere(GetActorLocation(), 200.f, true);
	CastSphere(GetActorLocation() + FVector(0.f, 0.f, 1000.f), 200.f, true);
}

bool AMapTile::CastSphere(FVector Location, float Radius, bool bDebugDraw = false)
{
	FHitResult OutHitResult;
	bool bHit = GetWorld()->SweepSingleByChannel(
		OutHitResult,
		Location,
		Location,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(Radius)
	);
	
	if (!bDebugDraw) return bHit;

	FColor SphereColor = bHit ? FColor::Red : FColor::Emerald;

	bool bPersistent = true;
	DrawDebugSphere(
		GetWorld(),
		Location,
		Radius,
		16,
		SphereColor,
		bPersistent
	);

	return bHit;
}

