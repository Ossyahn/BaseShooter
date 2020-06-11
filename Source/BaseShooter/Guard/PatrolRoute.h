// Copyright 2020 Alberto Romero Garcia, all rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PatrolRoute.generated.h"

/**
* List of waypoints to help AI follow a patrol route
*/

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BASESHOOTER_API UPatrolRoute : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPatrolRoute();
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	TArray<AActor*> GetWaypoints();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditInstanceOnly)
	TArray<AActor*> Waypoints;	

		
};
