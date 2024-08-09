// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/RaGLauncherWeapon.h"
#include "Weapon/RaGProjectile.h"

void ARaGLauncherWeapon::StartFire() {
    MakeShot();
}

void ARaGLauncherWeapon::MakeShot() {

    if (!GetWorld()) return;

    FVector TraceStart, TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd)) return;

    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
    const FVector Direction = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();


    const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleWorldLocation());
    ARaGProjectile* Projectile = GetWorld()->SpawnActorDeferred<ARaGProjectile>(ProjectileClass, SpawnTransform);

    if (Projectile)
    {
        Projectile->SetShotDirection(Direction);
        Projectile->SetOwner(GetOwner());
        Projectile->FinishSpawning(SpawnTransform);
    }

}
