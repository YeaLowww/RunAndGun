// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/RaGWeaponComponent.h"
#include "RaGAIWeaponComponent.generated.h"

/**
 * 
 */
UCLASS()
class RUNANDGUN_GIT_API URaGAIWeaponComponent : public URaGWeaponComponent
{
	GENERATED_BODY()

public:
    virtual void StartFire() override;
    virtual void NextWeapon() override;
};
