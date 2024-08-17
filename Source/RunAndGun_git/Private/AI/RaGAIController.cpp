// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/RaGAIController.h"
#include "AI/RaGAICharacter.h"
#include "Components/RaGAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

ARaGAIController::ARaGAIController() {

    RaGAIPerceptionComponent = CreateDefaultSubobject<URaGAIPerceptionComponent>("RaGAIPerceptionComponent");
    SetPerceptionComponent(*RaGAIPerceptionComponent);
}

void ARaGAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    const auto RaGCharacter = Cast<ARaGAICharacter>(InPawn);
    if (RaGCharacter)
    {
        RunBehaviorTree(RaGCharacter->BehaviorTreeAsset);
    }
}

void ARaGAIController::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);

    const auto AimActor = GetFocusOnActor();
    SetFocus(AimActor);

}

AActor* ARaGAIController::GetFocusOnActor() const
{
    if (!GetBlackboardComponent()) return nullptr;

    return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
