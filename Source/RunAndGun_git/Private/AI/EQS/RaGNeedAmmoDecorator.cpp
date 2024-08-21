// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EQS/RaGNeedAmmoDecorator.h"
#include "AIController.h"
#include "RaGUtils.h"
#include "Components/RaGWeaponComponent.h"

URaGNeedAmmoDecorator::URaGNeedAmmoDecorator() {
    NodeName = "Need Ammo";
}

bool URaGNeedAmmoDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    const auto Controller = OwnerComp.GetAIOwner();
    if (!Controller) return false;

    const auto WeaponComponent = RaGUtils::GetRaGPlayerComponent<URaGWeaponComponent>(Controller->GetPawn());
    if (!WeaponComponent) return false;

    return WeaponComponent->NeedAmmo(WeaponType);
}
