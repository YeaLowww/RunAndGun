// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/Services/RaGChangeWeaponService.h"
#include "AIController.h"
#include "RaGUtils.h"
#include "Components/RaGWeaponComponent.h"

URaGChangeWeaponService::URaGChangeWeaponService()
{
    NodeName = "ChangeWeapon";
}

void URaGChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

    const auto Controller = OwnerComp.GetAIOwner();

    if (Controller)
    {
        const auto WeaponComponent = RaGUtils::GetRaGPlayerComponent<URaGWeaponComponent>(Controller->GetPawn());
        if (WeaponComponent && Probability > 0 && FMath::FRand() <= Probability)
        {
            WeaponComponent->NextWeapon();
        }
    }
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}