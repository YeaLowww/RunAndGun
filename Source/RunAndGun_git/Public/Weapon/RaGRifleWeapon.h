// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/RaGBaseWeapon.h"
#include "RaGRifleWeapon.generated.h"

class URaGWeaponFXComponent;
class UNiagaraComponent;
class UNiagaraSystem;
    
UCLASS()
class RUNANDGUN_GIT_API ARaGRifleWeapon : public ARaGBaseWeapon
{
	GENERATED_BODY()
public:
    ARaGRifleWeapon();

    virtual void StartFire() override;
    virtual void StopFire() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float TimeBetweenShots = 0.1f;
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float BulletSpread = 1.5f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float DamageAmount = 10.0f;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UNiagaraSystem* TraceFX;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    FString TraceTargetName = "TraceTarget";

    UPROPERTY(VisibleAnywhere, Category = "VFX")
    URaGWeaponFXComponent* WeaponFXComponent;

    virtual void BeginPlay() override;
    virtual void MakeShot() override;
    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const override;

private:
    FTimerHandle ShotTimerHandle;

    UPROPERTY()
    UNiagaraComponent* MuzzleFXComponent;

    void MakeDamage(const FHitResult& HitResult);

    void InitMuzzleFX();
    void SetMuzzleFXVisibility(bool Visible);
    void SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd);

};
