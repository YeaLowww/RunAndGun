// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/RaGAICharacter.h"
#include "AI/RaGAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

ARaGAICharacter::ARaGAICharacter(const FObjectInitializer& ObjInit):Super(ObjInit) {
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = ARaGAIController::StaticClass();

    bUseControllerRotationYaw = false;
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
    }
}
