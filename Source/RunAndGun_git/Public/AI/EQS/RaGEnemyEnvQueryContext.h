// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "RaGEnemyEnvQueryContext.generated.h"

/**
 * 
 */
UCLASS()
class RUNANDGUN_GIT_API URaGEnemyEnvQueryContext : public UEnvQueryContext
{
	GENERATED_BODY()
	
public:
    virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;



protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    FName EnemyActorKeyName = "EnemyActor";

};
