// Copyright 2020 Alberto Romero Garcia, all rights reserved.


#include "ChooseNextWaypoint.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UE_LOG(LogTemp, Warning, TEXT("ChooseNextWaypoint task executed"));
	return EBTNodeResult::Succeeded;
}
