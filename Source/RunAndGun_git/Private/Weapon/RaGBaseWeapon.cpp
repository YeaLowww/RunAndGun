

#include "Weapon/RaGBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"


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
	
}
void ARaGBaseWeapon::Fire() {

	UE_LOG(LogBaseWeapon, Display, TEXT("Fire!"));

}