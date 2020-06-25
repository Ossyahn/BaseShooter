// Copyright 2020 Alberto Romero Garcia, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHealthDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BASESHOOTER_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	UFUNCTION(BlueprintCallable, Category = "Damage")
	virtual void DealDamage(float Damage);

	UFUNCTION(BlueprintCallable, Category = "Damage")
	virtual bool HasNoHealth();

	UFUNCTION(BlueprintCallable, Category = "Damage")
	virtual void Kill();

	UPROPERTY(BlueprintCallable, Category = "Death")
	FHealthDelegate OnNoHealth;

	//TODO: Make private through functions
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float Health = 100;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Health")
	float MaxHealth = 100;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	bool bNoHealth = false;
		
};
