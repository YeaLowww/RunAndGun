// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/RaGHealthComponent.h"
#include "GameFramework/Actor.h"
#include "Dev/RaGFireDamageType.h"
#include "Dev/RaGIceDamageType.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

URaGHealthComponent::URaGHealthComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

}


// Called when the game starts
void URaGHealthComponent::BeginPlay()
{
	Super::BeginPlay();
    Health = MaxHealth;

    AActor* ComponentOwner = GetOwner();
    if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &URaGHealthComponent::OnTakeAnyDamage);
    }

}
void URaGHealthComponent::OnTakeAnyDamage(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    Health -= Damage;
    UE_LOG(LogHealthComponent, Display, TEXT("Damage: %f"), Damage);

    if (DamageType)
    {
        if (DamageType->IsA<URaGFireDamageType>())
        {
            UE_LOG(LogHealthComponent, Display, TEXT("Fire Damage!"));
        }
        else if (DamageType->IsA<URaGIceDamageType>())
        {
            UE_LOG(LogHealthComponent, Display, TEXT("Ice Damage!"));
        }
        
    }
}
