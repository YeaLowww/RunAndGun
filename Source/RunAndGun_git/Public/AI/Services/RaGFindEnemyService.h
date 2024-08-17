// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "RaGFindEnemyService.generated.h"

/**
 * 
 */
UCLASS()
class RUNANDGUN_GIT_API URaGFindEnemyService : public UBTService
{
	GENERATED_BODY()
	
public:
    URaGFindEnemyService();


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector EnemyActorKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
