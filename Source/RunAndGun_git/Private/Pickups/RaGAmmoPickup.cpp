// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/RaGAmmoPickup.h"
#include "Components/RaGHealthComponent.h"
#include "Components/RaGWeaponComponent.h"
#include "RaGUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickups, All, All);

bool ARaGAmmoPickup::GivePickupTo(APawn* PlayerPawn)
{
    const auto HealthComponent = RaGUtils::GetRaGPlayerComponent<URaGHealthComponent>(PlayerPawn);
    if (!HealthComponent || HealthComponent->IsDead()) return false;

    const auto WeaponComponent = RaGUtils::GetRaGPlayerComponent<URaGWeaponComponent>(PlayerPawn);
    if (!WeaponComponent) return false;

    return WeaponComponent->TryToGetAmmo(WeaponType, ClipsAmount);
}
