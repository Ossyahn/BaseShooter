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
	SpawnBox->InitBoxExtent(FVector(100.f, 100.f, 0.f));
	SpawnBox->SetupAttachment(RootComponent);
}

void AMapTile::SpawnActorsRandomly(TSubclassOf<AActor> ToSpawn, int MinAmount = 1, int MaxAmount = 1)
{
	int Amount = FMath::RandRange(MinAmount, MaxAmount);

	for (int i = 0; i <= Amount; i++) 
	{
		AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ToSpawn);
		float BoundsRadius = GetBoundsRadius(SpawnedActor);
		FVector OutRandomWorldLocation;
		bool bEmpty = GetEmptyRandomLocation(BoundsRadius, OutRandomWorldLocation);
		if (bEmpty) 
		{
			SpawnedActor->SetActorLocation(OutRandomWorldLocation);
			SpawnedActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));
		}
		else
		{
			SpawnedActor->Destroy();
		}
	}
}

// Called when the game starts or when spawned
void AMapTile::BeginPlay()
{
	Super::BeginPlay();
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

bool AMapTile::GetEmptyRandomLocation(float BoundsRadius, FVector& OutRandomWorldLocation)
{
	FVector BoxCenter = SpawnBox->GetComponentLocation();
	FVector MinPoint = BoxCenter - SpawnBox->GetScaledBoxExtent();
	FVector MaxPoint = BoxCenter + SpawnBox->GetScaledBoxExtent();

	for (int i = 0; i <= MaxTries; i++) 
	{
		FVector RandomWorldLocation = FMath::RandPointInBox(FBox(MinPoint, MaxPoint));
		bool bHit = CastSphere(RandomWorldLocation, BoundsRadius, true);
		if (!bHit) 
		{
			OutRandomWorldLocation = RandomWorldLocation;
			return true;
		}
	}
	return false;
}

float AMapTile::GetBoundsRadius(AActor* Actor)
{
	FVector OutActorOrigin;
	FVector OutActorExtent;

	Actor->GetActorBounds(true, OutActorOrigin, OutActorExtent);

	return OutActorExtent.Size();
}

