
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RaGWeaponComponent.generated.h"

class ARaGBaseWeapon;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RUNANDGUN_GIT_API URaGWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	URaGWeaponComponent();
    void Fire();

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TSubclassOf<ARaGBaseWeapon> WeaponClass;
	
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponAttachPointName = "WeaponSocket";


    virtual void BeginPlay() override;

private:
    UPROPERTY()
    ARaGBaseWeapon* CurrentWeapon = nullptr;

    void SpawnWeapon();
};
