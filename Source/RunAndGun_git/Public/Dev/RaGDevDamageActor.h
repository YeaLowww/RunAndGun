// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RaGDevDamageActor.generated.h"

UCLASS()
class RUNANDGUN_GIT_API ARaGDevDamageActor : public AActor
{
	GENERATED_BODY()
	
public:	

	ARaGDevDamageActor();

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
    USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Radius = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FColor SphereColor = FColor::Red;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Damage = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool DoFullDamage = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UDamageType> DamageType;


protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

};
