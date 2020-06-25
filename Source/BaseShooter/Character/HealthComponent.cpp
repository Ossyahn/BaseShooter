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

// Reduce health property to a min of 0
void UHealthComponent::DealDamage(float Damage)
{
	Health -= fmod(Damage, Health);
	if (HasHealth()) {
		OnNoHealth.Broadcast();
	}
}

bool UHealthComponent::HasHealth()
{
	return Health == 0;
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


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

