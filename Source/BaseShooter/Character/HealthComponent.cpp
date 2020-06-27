// Copyright 2020 Alberto Romero Garcia, all rights reserved.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

/// Reduce health property to a min of 0
void UHealthComponent::DealDamage(float Damage)
{
	if (bNoHealth) return;

	FMath::Clamp<float>(Damage, 0, Health);
	Health -= Damage;

	if (Health == 0) {
		UE_LOG(LogTemp, Warning, TEXT("OnNoHealth broadcast"));

		bNoHealth = true;
		OnNoHealth.Broadcast();
	}
}

bool UHealthComponent::HasNoHealth()
{
	return bNoHealth;
}

void UHealthComponent::Kill()
{
	DealDamage(Health);
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;	
}

