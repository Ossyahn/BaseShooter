// Copyright 2020 Alberto Romero Garcia, all rights reserved.


#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{	
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	int IndexVal = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);

	UE_LOG(LogTemp, Warning, TEXT("Waypoint index: %i"), IndexVal);


	return EBTNodeResult::Succeeded;
}
