
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RaGBaseWeapon.generated.h"


class USkeletalMeshComponent;

UCLASS()
class RUNANDGUN_GIT_API ARaGBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ARaGBaseWeapon();
    virtual void Fire();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* WeaponMesh;

	virtual void BeginPlay() override;


};
