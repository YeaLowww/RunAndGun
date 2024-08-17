// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "RaGAIController.generated.h"

class URaGAIPerceptionComponent;

UCLASS()
class RUNANDGUN_GIT_API ARaGAIController : public AAIController
{
    GENERATED_BODY()

public:
    ARaGAIController();


protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    URaGAIPerceptionComponent* RaGAIPerceptionComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FName FocusOnKeyName = "EnemyActor";


    virtual void OnPossess(APawn* InPawn) override;
    virtual void Tick(float DeltaTime) override;

private:
    AActor* GetFocusOnActor() const;
};
