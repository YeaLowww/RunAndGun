
#include "Weapon/RaGBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All)

ARaGBaseWeapon::ARaGBaseWeapon()
{

    PrimaryActorTick.bCanEverTick = false;
    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);
}

void ARaGBaseWeapon::BeginPlay()
{
    Super::BeginPlay();
    check(WeaponMesh);
    checkf(DefaultAmmo.Bullets > 0, TEXT("Bullets count couldn't be less or equal zero"));
    checkf(DefaultAmmo.Clips > 0, TEXT("Clips count couldn't be less or equal zero"));
    CurrentAmmo = DefaultAmmo;
}

void ARaGBaseWeapon::StartFire() {}
void ARaGBaseWeapon::StopFire() {}

void ARaGBaseWeapon::MakeShot() {}

APlayerController* ARaGBaseWeapon::GetPlayerController() const
{
    const auto Player = Cast<ACharacter>(GetOwner());
    if (!Player) return nullptr;

    return Player->GetController<APlayerController>();
}

bool ARaGBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{

    const auto Controller = GetPlayerController();
    if (!Controller) return false;

    Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
    return true;
}

FVector ARaGBaseWeapon::GetMuzzleWorldLocation() const
{

    return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

bool ARaGBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{

    FVector ViewLocation;
    FRotator ViewRotation;
    if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

    TraceStart = ViewLocation;

    const FVector ShotDirection = ViewRotation.Vector();
    TraceEnd = TraceStart + ShotDirection * TraceMaxDistance;
    return true;
}

void ARaGBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
    if (!GetWorld()) return;

    FCollisionQueryParams CollisionParams;
    CollisionParams.bReturnPhysicalMaterial = true;
    CollisionParams.AddIgnoredActor(GetOwner());
    CollisionParams.bReturnPhysicalMaterial = true;

    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, CollisionParams);
}

void ARaGBaseWeapon::DercreaseAmmo()
{
    if (CurrentAmmo.Bullets == 0)
    {
        UE_LOG(LogBaseWeapon, Warning, TEXT("----No Bullets in Clip----"));
        return;
    }

    CurrentAmmo.Bullets--;
    // LogAmmo();

    if (IsClipEmpty() && !IsAmmoEmpty())
    {
        StopFire();
        OnClipEmpty.Broadcast(this);
    }
}

bool ARaGBaseWeapon::IsAmmoEmpty() const
{
    return !CurrentAmmo.Infinite && CurrentAmmo.Clips == 0 && IsClipEmpty();
}

bool ARaGBaseWeapon::IsClipEmpty() const
{
    return CurrentAmmo.Bullets == 0;
}

bool ARaGBaseWeapon::IsAmmoFull() const
{
    return CurrentAmmo.Clips == DefaultAmmo.Clips &&    //
           CurrentAmmo.Bullets == DefaultAmmo.Bullets;  //
}

void ARaGBaseWeapon::ChangeClip()
{

    if (!CurrentAmmo.Infinite)
    {
        if (CurrentAmmo.Clips == 0)
        {
            UE_LOG(LogBaseWeapon, Warning, TEXT("----No more Clips----"));
            return;
        }
        CurrentAmmo.Clips--;
    }
    CurrentAmmo.Bullets = DefaultAmmo.Bullets;

    UE_LOG(LogBaseWeapon, Display, TEXT("----Change Clip----"));
}

bool ARaGBaseWeapon::CanReload() const
{
    return CurrentAmmo.Bullets < DefaultAmmo.Bullets && CurrentAmmo.Clips > 0;
}

void ARaGBaseWeapon::LogAmmo()
{
    FString AmmoInfo = "Ammo: " + FString::FromInt(CurrentAmmo.Bullets) + " / ";
    AmmoInfo += CurrentAmmo.Infinite ? "Infinite " : FString::FromInt(CurrentAmmo.Clips);
    UE_LOG(LogBaseWeapon, Display, TEXT("%s"), *AmmoInfo);
}

bool ARaGBaseWeapon::TryToGetAmmo(int32 ClipsAmount)
{
    if (CurrentAmmo.Infinite || IsAmmoFull() || ClipsAmount <= 0) return false;

    if (IsAmmoEmpty())
    {
        UE_LOG(LogBaseWeapon, Display, TEXT("Ammo was empty"));
        CurrentAmmo.Clips = FMath::Clamp(ClipsAmount, 0, DefaultAmmo.Clips + 1);
        OnClipEmpty.Broadcast(this);
    }
    else if (CurrentAmmo.Clips < DefaultAmmo.Clips)
    {
        const auto NextClipsAmount = CurrentAmmo.Clips + ClipsAmount;
        if (DefaultAmmo.Clips - NextClipsAmount >= 0)
        {
            CurrentAmmo.Clips = NextClipsAmount;
            UE_LOG(LogBaseWeapon, Display, TEXT("Clips were added"));
        }
        else
        {
            CurrentAmmo.Clips = DefaultAmmo.Clips;
            CurrentAmmo.Bullets = DefaultAmmo.Bullets;
            UE_LOG(LogBaseWeapon, Display, TEXT("Ammo is full now"));
        }
    }
    else
    {
        CurrentAmmo.Bullets = DefaultAmmo.Bullets;
        UE_LOG(LogBaseWeapon, Display, TEXT("Bullets were added"));
    }
    return true;
}

UNiagaraComponent* ARaGBaseWeapon::SpawnMuzzleFX()
{
    return UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleFX,  //
        WeaponMesh,                                           //
        MuzzleSocketName,                                     //
        FVector::ZeroVector,                                  //
        FRotator::ZeroRotator,                                //
        EAttachLocation::SnapToTarget,                        //
        true);                                                //
}