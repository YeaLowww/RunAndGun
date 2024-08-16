// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/RaGRifleWeapon.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Engine\DamageEvents.h"
#include "Weapon/Components/RaGWeaponFXComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

ARaGRifleWeapon::ARaGRifleWeapon() {
    WeaponFXComponent = CreateDefaultSubobject<URaGWeaponFXComponent>("WeaponFXComponent");
}

void ARaGRifleWeapon::StartFire()
{
    InitMuzzleFX();
    GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ARaGRifleWeapon::MakeShot, TimeBetweenShots, true);
    MakeShot();
}
void ARaGRifleWeapon::StopFire()
{
    GetWorldTimerManager().ClearTimer(ShotTimerHandle);
    SetMuzzleFXVisibility(false);
}

void ARaGRifleWeapon::BeginPlay() {
    Super::BeginPlay();
    check(WeaponFXComponent);
}

void ARaGRifleWeapon::MakeShot()
{

    if (!GetWorld() || IsAmmoEmpty())
    {
        StopFire();
        return;
    }

    FVector TraceStart, TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd))
    {
        StopFire();
        return;
    }

    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    FVector TraceFXEnd = TraceEnd;
    if (HitResult.bBlockingHit)
    {
        TraceFXEnd = HitResult.ImpactPoint;
        MakeDamage(HitResult);
        //DrawDebugLine(GetWorld(), GetMuzzleWorldLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);
        //DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Red, false, 5.0f);
        WeaponFXComponent->PlayImpactFX(HitResult);
    }
    SpawnTraceFX(GetMuzzleWorldLocation(), TraceFXEnd);
    DercreaseAmmo();
}

bool ARaGRifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{

    FVector ViewLocation;
    FRotator ViewRotation;
    if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

    TraceStart = ViewLocation;

    const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
    const FVector ShotDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
    TraceEnd = TraceStart + ShotDirection * TraceMaxDistance;
    return true;
}

void ARaGRifleWeapon::MakeDamage(const FHitResult& HitResult)
{

    const auto DamagedActor = HitResult.GetActor();
    if (!DamagedActor) return;

    DamagedActor->TakeDamage(DamageAmount, FDamageEvent(), GetPlayerController(), this);
}

void ARaGRifleWeapon::InitMuzzleFX() {
    if (!MuzzleFXComponent)
    {
        MuzzleFXComponent = SpawnMuzzleFX();
    }
    SetMuzzleFXVisibility(true);
}

void ARaGRifleWeapon::SetMuzzleFXVisibility(bool Visible) {
    if (MuzzleFXComponent)
    {
        MuzzleFXComponent->SetPaused(!Visible);
        MuzzleFXComponent->SetVisibility(Visible, true);
    }


}

void ARaGRifleWeapon::SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd) {

    const auto TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceFX, TraceStart);
    if (TraceFXComponent)
    {
        TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName, TraceEnd);
    }
}
