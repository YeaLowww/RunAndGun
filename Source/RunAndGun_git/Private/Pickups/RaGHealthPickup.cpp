// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/RaGHealthPickup.h"
#include "Components/RaGHealthComponent.h"
#include "RaGUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickups, All, All);


bool ARaGHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
    //UE_LOG(LogHealthPickups, Display, TEXT("Health was taken"));
    const auto HealthComponent = RaGUtils::GetRaGPlayerComponent<URaGHealthComponent>(PlayerPawn);
    if (!HealthComponent) return false;

    return HealthComponent->TryToGetHealth(HealthAmount);
}

