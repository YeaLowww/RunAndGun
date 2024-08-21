// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "RaGHealthPercentDecorator.generated.h"

/**
 * 
 */
UCLASS()
class RUNANDGUN_GIT_API URaGHealthPercentDecorator : public UBTDecorator
{
	GENERATED_BODY()
	
public:
    URaGHealthPercentDecorator();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float HealthPercent = 0.6f;

    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
