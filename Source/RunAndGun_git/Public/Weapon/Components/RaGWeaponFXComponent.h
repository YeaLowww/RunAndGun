
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RaGCoreTypes.h"
#include "RaGWeaponFXComponent.generated.h"

class UNiagaraSystem;
class UPhysicalMaterial;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class RUNANDGUN_GIT_API URaGWeaponFXComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    URaGWeaponFXComponent();
    void PlayImpactFX(const FHitResult& Hit);

protected:
    virtual void BeginPlay() override;
    
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    FImpactData DefaultImpactData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    TMap<UPhysicalMaterial*, FImpactData> ImpactDataMap;
};
