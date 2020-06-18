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

void AMapTile::SpawnActorsRandomly(TSubclassOf<AActor> ToSpawn, int MinAmount, int MaxAmount, TEnumAsByte<SpawnRotation> SpawnRotation, bool bRandomScale)
{
	int Amount = FMath::RandRange(MinAmount, MaxAmount);

	for (int i = 0; i < Amount; i++) 
	{
		//Spawning actor before finding empty location to know its dimensions
		AActor* SpawnedActor = SpawnActor(ToSpawn, SpawnRotation, bRandomScale);
		float BoundsRadius = GetBoundsRadius(SpawnedActor);
		FVector OutRandomWorldLocation;
		bool bEmpty = GetEmptyRandomLocation(BoundsRadius, OutRandomWorldLocation);
		if (bEmpty) 
		{
			SpawnedActor->SetActorLocation(OutRandomWorldLocation);
			SpawnedActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepWorld, true));
			
			GetBoundsRadius(SpawnedActor, true);
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

bool AMapTile::CastSphere(FVector Location, float Radius, bool bDebugDraw)
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

//Finds an spherical empty location the size of BoundsRadius inside SpawnBox. ng it in the OutRandomWorldLocation reference.
// Returns true if an empty location was found, false if OutRandomWorldLocation is invalid. The number of tries 
// depends on the MaxTries property
bool AMapTile::GetEmptyRandomLocation(float BoundsRadius, FVector& OutRandomWorldLocation)
{
	FVector BoxCenter = SpawnBox->GetComponentLocation();
	FVector MinPoint = BoxCenter - SpawnBox->GetScaledBoxExtent();
	FVector MaxPoint = BoxCenter + SpawnBox->GetScaledBoxExtent();

	for (int i = 0; i < MaxTries; i++) 
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

//Finds the radius of the smaller possible sphere containing the bounds of the actor within.
float AMapTile::GetBoundsRadius(AActor* Actor, bool bDebugDraw)
{
	FVector OutActorOrigin;
	FVector OutActorExtent;

	Actor->GetActorBounds(true, OutActorOrigin, OutActorExtent);

	if (!bDebugDraw) return OutActorExtent.Size();

	DrawDebugBox(GetWorld(), OutActorOrigin, OutActorExtent, FColor::Blue, true);
	DrawDebugLine(GetWorld(), OutActorOrigin, OutActorOrigin + OutActorExtent, FColor::Yellow, true);

	return OutActorExtent.Size();
}

AActor* AMapTile::SpawnActor(TSubclassOf<AActor> ToSpawn, TEnumAsByte<SpawnRotation> SpawnRotation, bool bRandomScale)
{
	FTransform Transform = FTransform();

	if (SpawnRotation == SpawnRotation::RandomAllAxis) 
	{
		float Pitch = FMath::RandRange(0.f, 360.f);
		float Yaw = FMath::RandRange(0.f, 360.f);
		float Roll = FMath::RandRange(0.f, 360.f);
		Transform.SetRotation(FQuat(FRotator(Pitch, Yaw, Roll)));
	}
	else if (SpawnRotation == SpawnRotation::RandomYaw) 
	{
		float Yaw = FMath::RandRange(0.f, 360.f);
		Transform.SetRotation(FQuat(FRotator(0.f, Yaw, 0.f)));
	}
	
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ToSpawn, Transform);

	if (bRandomScale)
	{
		float Scale = FMath::RandRange(MinRandomScaling, MaxRandomScaling);
		SpawnedActor->SetActorScale3D(FVector(Scale));
	}

	return SpawnedActor;
}

