// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/RaGCharacterMovementComponent.h"
#include "Player/RaGBaseCharacter.h"

float URaGCharacterMovementComponent::GetMaxSpeed() const
{
    const float MaxSpeed = Super::GetMaxSpeed();
    const ARaGBaseCharacter* Player = Cast<ARaGBaseCharacter>(GetPawnOwner());

    return Player && Player->isRunning() ? MaxSpeed * RunModifier : MaxSpeed;
}
