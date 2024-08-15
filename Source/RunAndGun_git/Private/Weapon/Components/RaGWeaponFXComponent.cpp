

#include "Weapon/Components/RaGWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

URaGWeaponFXComponent::URaGWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void URaGWeaponFXComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void URaGWeaponFXComponent::PlayImpactFX(const FHitResult& Hit) {
    auto Effect = DefaultEffect;

	if (Hit.PhysMaterial.IsValid())
    {
        const auto PhysMat = Hit.PhysMaterial.Get();
        if (EffectsMap.Contains(PhysMat))
        {
            Effect = EffectsMap[PhysMat];
        }
	}
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());

}


