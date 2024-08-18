// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/RaGBaseCharacter.h"
#include "RaGAICharacter.generated.h"

class UBehaviorTree;
UCLASS()
class RUNANDGUN_GIT_API ARaGAICharacter : public ARaGBaseCharacter
{
	GENERATED_BODY()
public:
    ARaGAICharacter(const FObjectInitializer& ObjInit);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    UBehaviorTree* BehaviorTreeAsset;

protected:
    virtual void OnDeath() override;
};
