// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/RaGBasePickup.h"
#include "RaGAmmoPickup.generated.h"

class ARaGBaseWeapon;

UCLASS()
class RUNANDGUN_GIT_API ARaGAmmoPickup : public ARaGBasePickup
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickups", meta = (ClampMin = "1.0", ClampMax = "10.0"))
    int32 ClipsAmount = 10;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickups")
    TSubclassOf<ARaGBaseWeapon> WeaponType;

private:
    virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
