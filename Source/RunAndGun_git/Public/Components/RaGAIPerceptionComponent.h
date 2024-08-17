// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "RaGAIPerceptionComponent.generated.h"

/**
 * 
 */
UCLASS()
class RUNANDGUN_GIT_API URaGAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()

public:
    AActor* GetClosestEnemy() const;
};
