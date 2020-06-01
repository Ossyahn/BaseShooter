// Copyright 2020 Alberto Romero Garcia, all rights reserved.


#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrolRoute.h"


EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto Pawn = OwnerComp.GetAIOwner()->GetPawn();
	auto PatrolRouteComponent = Pawn->FindComponentByClass<UPatrolRoute>();
	if (!ensure(PatrolRouteComponent)) return EBTNodeResult::Failed;

	TArray<AActor*> Waypoints = PatrolRouteComponent->GetWaypoints();
	if (Waypoints.Num() == 0) return EBTNodeResult::Failed;

	auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (!ensure(Blackboard)) return EBTNodeResult::Failed;

	int Index = Blackboard->GetValueAsInt(IndexKey.SelectedKeyName);
	auto NextWaypoint = Waypoints[Index];
	
	Blackboard->SetValueAsObject(WaypointKey.SelectedKeyName, NextWaypoint);

	Index++;
	Index %= Waypoints.Num();
	Blackboard->SetValueAsInt(IndexKey.SelectedKeyName, Index);

	return EBTNodeResult::Succeeded;
}

