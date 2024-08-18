// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/RaGAICharacter.h"
#include "AI/RaGAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/RaGAIWeaponComponent.h"
#include "BrainComponent.h"

ARaGAICharacter::ARaGAICharacter(const FObjectInitializer& ObjInit) : Super(ObjInit.SetDefaultSubobjectClass<URaGAIWeaponComponent>("WeaponComponent"))
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = ARaGAIController::StaticClass();

    bUseControllerRotationYaw = false;
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
    }
}

void ARaGAICharacter::OnDeath() {
    
    Super::OnDeath();

    const auto RaGController = Cast<AAIController>(Controller);
    if (RaGController && RaGController->BrainComponent)
    {
        RaGController->BrainComponent->Cleanup();
    }

}
