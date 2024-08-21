
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RaGCoreTypes.h"
#include "Weapon/RaGBaseWeapon.h"
#include "RaGWeaponComponent.generated.h"

class ARaGBaseWeapon;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class RUNANDGUN_GIT_API URaGWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    URaGWeaponComponent();
    virtual void StartFire();
    void StopFire();
    virtual void NextWeapon();
    void Reload();

    bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;
    bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;

    bool TryToGetAmmo(TSubclassOf<ARaGBaseWeapon> WeaponType, int32 ClipsAmount);
    bool NeedAmmo(TSubclassOf<ARaGBaseWeapon> WeaponType);

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TArray<FWeaponData> WeaponData;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponEquipSocketName = "WeaponSocket";

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponArmorySocketName = "ArmorySocket";

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* EquipAnimMontage;

    UPROPERTY()
    ARaGBaseWeapon* CurrentWeapon = nullptr;

    UPROPERTY()
    TArray<ARaGBaseWeapon*> Weapons;

    int32 CurrentWeaponIndex = 0;

    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    bool CanFire() const;
    bool CanEquip() const;
    void EquipWeapon(int32 WeaponIndex);

private:
    UPROPERTY()
    UAnimMontage* CurrentReloadAnimMontage = nullptr;

    bool EquipAnimInProgress = false;
    bool ReloadAnimInProgress = false;

    void SpawnWeapons();
    void AttachWeaponToSocket(ARaGBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
    
    void PlayAnimMontage(UAnimMontage* Animation);
    void InitAnimation();
    void OnEquipFinished(USkeletalMeshComponent* MeshComp);
    void OnReloadFinished(USkeletalMeshComponent* MeshComp);

    bool CanReload() const;

    void OnClipEmpty(ARaGBaseWeapon* AmmoEmptyWeapon);
    void ChangeClip();
};
