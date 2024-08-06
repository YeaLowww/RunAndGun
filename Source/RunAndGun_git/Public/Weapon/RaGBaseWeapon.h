
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

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    FName MuzzleSocketName = "MuzzleSocket";


    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float TraceMaxDistance = 1500.0f;



	virtual void BeginPlay() override;

	void MakeShot();

};
