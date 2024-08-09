
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RaGWeaponComponent.generated.h"

class ARaGBaseWeapon;
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class RUNANDGUN_GIT_API URaGWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    URaGWeaponComponent();
    void StartFire();
    void StopFire();
    void NextWeapon();

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TArray<TSubclassOf<ARaGBaseWeapon>> WeaponClasses;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponEquipSocketName = "WeaponSocket";
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponArmorySocketName = "ArmorySocket";

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* EquipAnimMontage;

    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
    UPROPERTY()
    ARaGBaseWeapon* CurrentWeapon = nullptr;

    UPROPERTY()
    TArray<ARaGBaseWeapon*> Weapons;
    int32 CurrentWeaponIndex = 0;
    bool EquipAnimInProgress = false;

    void SpawnWeapons();
    void AttachWeaponToSocket(ARaGBaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
    void EquipWeapon(int32 WeaponIndex);
    
    void PlayAnimMontage(UAnimMontage* Animation);
    void InitAnimation();
    void OnEquipFinished(USkeletalMeshComponent* MeshComponent);

    bool CanFire() const;
    bool CanEquip() const;
};
