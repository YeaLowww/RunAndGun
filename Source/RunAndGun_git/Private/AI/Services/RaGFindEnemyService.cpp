// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/RaGFindEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "RaGUtils.h"
#include "Components/RaGAIPerceptionComponent.h"

URaGFindEnemyService::URaGFindEnemyService() {

	NodeName = "Find Enemy";
}

void URaGFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {

	const auto Blackboard = OwnerComp.GetBlackboardComponent();
    if (Blackboard)
    {
        const auto Controller = OwnerComp.GetAIOwner();
        const auto PerceptionComponent = RaGUtils::GetRaGPlayerComponent<URaGAIPerceptionComponent>(Controller);
        if (PerceptionComponent)
        {
            Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
        }


    }
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
