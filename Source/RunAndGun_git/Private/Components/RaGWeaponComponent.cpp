

#include "Components/RaGWeaponComponent.h"
#include "Weapon/RaGBaseWeapon.h"
#include "GameFramework/Character.h"
URaGWeaponComponent::URaGWeaponComponent()
{

    PrimaryComponentTick.bCanEverTick = false;
}


void URaGWeaponComponent::BeginPlay()
{
    Super::BeginPlay();
    SpawnWeapon();
}

void URaGWeaponComponent::SpawnWeapon()
{
    if (!GetWorld()) return;
    
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character) return;

    CurrentWeapon = GetWorld()->SpawnActor<ARaGBaseWeapon>(WeaponClass);
    if (!CurrentWeapon) return;
   
    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachPointName);
    CurrentWeapon->SetOwner(Character);


}
void URaGWeaponComponent::StartFire()
{

    if (!CurrentWeapon) return;
    CurrentWeapon->StartFire();
}
void URaGWeaponComponent::StopFire()
{

    if (!CurrentWeapon) return;
    CurrentWeapon->StopFire();
}