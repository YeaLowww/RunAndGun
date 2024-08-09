// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/RaGBaseWeapon.h"
#include "RaGLauncherWeapon.generated.h"

/**
 * 
 */
class ARaGProjectile;


UCLASS()
class RUNANDGUN_GIT_API ARaGLauncherWeapon : public ARaGBaseWeapon
{
	GENERATED_BODY()
public:
    virtual void StartFire() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<ARaGProjectile> ProjectileClass;

    virtual void MakeShot() override;

};
