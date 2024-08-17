// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/RaGAIPerceptionComponent.h"
#include "AIController.h"
#include "RaGUtils.h"
#include "Components/RaGHealthComponent.h"
#include "Perception/AISense_Sight.h"

AActor* URaGAIPerceptionComponent::GetClosestEnemy() const
{
    TArray<AActor*> PercieveActors;
    GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);
    if (PercieveActors.Num() == 0) return nullptr;

    const auto Controller = Cast<AAIController>(GetOwner());
    if (!Controller) return nullptr;

    const auto Pawn = Controller->GetPawn();
    if (!Pawn) return nullptr;

    float BestDistance = MAX_FLT;
    AActor* BestPawn = nullptr;
    for (const auto PercieveActor : PercieveActors)
    {
        const auto HealthComponent = RaGUtils::GetRaGPlayerComponent<URaGHealthComponent>(PercieveActor);
        if (HealthComponent && !HealthComponent->IsDead()) // TODO: check if enemy
        {
            const auto CurrentDistance = (PercieveActor->GetActorLocation() - Pawn->GetActorLocation()).Size(); 
            if (CurrentDistance < BestDistance)
            {
                BestDistance = CurrentDistance;
                BestPawn = PercieveActor;
            }
        }
    }
    return BestPawn;
}
