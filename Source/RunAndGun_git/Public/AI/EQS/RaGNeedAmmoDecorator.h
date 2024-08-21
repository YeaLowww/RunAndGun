// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "RaGNeedAmmoDecorator.generated.h"

class ARaGBaseWeapon;


UCLASS()
class RUNANDGUN_GIT_API URaGNeedAmmoDecorator : public UBTDecorator
{
	GENERATED_BODY()
	
public:
    URaGNeedAmmoDecorator();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    TSubclassOf<ARaGBaseWeapon> WeaponType;

    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
