// Copyright 2020 Alberto Romero Garcia, all rights reserved.


#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
//#include "PatrollingGuard.h"


EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{	
	auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard) return EBTNodeResult::Failed;

	int Index = Blackboard->GetValueAsInt(IndexKey.SelectedKeyName);

	auto Pawn = OwnerComp.GetAIOwner()->GetPawn();
	//APatrollingGuard* Guard = Cast<APatrollingGuard>(Pawn);
	//TArray<AActor> Waypoints = Guard->

	//UE_LOG(LogTemp, Warning, TEXT("Waypoint index: %i"), Index);


	return EBTNodeResult::Succeeded;
}

