// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/RaGPlayerHUDWidget.h"
#include "Components/RaGHealthComponent.h"
#include "Components/RaGWeaponComponent.h"
#include "RaGUtils.h"

float URaGPlayerHUDWidget::GetHealthPercent() const
{
    const auto HealthComponent = RaGUtils::GetRaGPlayerComponent<URaGHealthComponent>(GetOwningPlayerPawn());
    if (!HealthComponent) return 0.0f;

    return HealthComponent->GetHealthPercent();
}

bool URaGPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{

    const auto WeaponComponent = RaGUtils::GetRaGPlayerComponent<URaGWeaponComponent>(GetOwningPlayerPawn());
    if (!WeaponComponent) return false;

    return WeaponComponent->GetCurrentWeaponUIData(UIData);
}

bool URaGPlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
{
    const auto WeaponComponent = RaGUtils::GetRaGPlayerComponent<URaGWeaponComponent>(GetOwningPlayerPawn());
    if (!WeaponComponent) return false;

    return WeaponComponent->GetCurrentWeaponAmmoData(AmmoData);
}


bool URaGPlayerHUDWidget::IsPlayerAlive() const
{
    const auto HealthComponent = RaGUtils::GetRaGPlayerComponent<URaGHealthComponent>(GetOwningPlayerPawn());
    return HealthComponent && !HealthComponent->IsDead();
}
bool URaGPlayerHUDWidget::IsPlayerSpectating() const
{
    const auto Controller = GetOwningPlayer();
    return Controller && Controller->GetStateName() == NAME_Spectating;
}