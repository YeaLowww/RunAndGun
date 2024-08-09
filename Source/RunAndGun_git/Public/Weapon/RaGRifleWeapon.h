// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/RaGBaseWeapon.h"
#include "RaGRifleWeapon.generated.h"

/**
 * 
 */
UCLASS()
class RUNANDGUN_GIT_API ARaGRifleWeapon : public ARaGBaseWeapon
{
	GENERATED_BODY()
public:
    
    virtual void StartFire() override;
    virtual void StopFire() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float TimeBetweenShots = 0.1f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float BulletSpread = 1.5f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float DamageAmount = 10.0f;

    virtual void MakeShot() override;
    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

private:
    FTimerHandle ShotTimerHandle;
    void MakeDamage(const FHitResult& HitResult);
};
