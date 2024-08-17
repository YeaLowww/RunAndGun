// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/RaGFireService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "RaGUtils.h"
#include "Components/RaGWeaponComponent.h"

URaGFireService::URaGFireService() {
    NodeName = "Fire";
}

void URaGFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) {
    
    const auto Controller = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    
    const auto HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

    if (Controller)
    {
        const auto WeaponComponent = RaGUtils::GetRaGPlayerComponent<URaGWeaponComponent>(Controller->GetPawn());
        if (WeaponComponent)
        {
            HasAim ? WeaponComponent->StartFire() : WeaponComponent->StopFire();
        }
    }
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

}
