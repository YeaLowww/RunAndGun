// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorators/RaGHealthPercentDecorator.h"
#include "AIController.h"
#include "RaGUtils.h"
#include "Components/RaGHealthComponent.h"

URaGHealthPercentDecorator::URaGHealthPercentDecorator() {
    NodeName = "Health Percent";
}

bool URaGHealthPercentDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    const auto Controller = OwnerComp.GetAIOwner();
    if (!Controller) return false;

    const auto HealthComponent = RaGUtils::GetRaGPlayerComponent<URaGHealthComponent>(Controller->GetPawn());
    if (!HealthComponent || HealthComponent->IsDead()) return false;

    return HealthComponent->GetHealthPercent() <= HealthPercent;
}
