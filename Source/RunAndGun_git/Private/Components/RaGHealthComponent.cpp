// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/RaGHealthComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "TimerManager.h"


DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

URaGHealthComponent::URaGHealthComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

}

bool URaGHealthComponent::TryToGetHealth(float HealthAmount)
{
    if (IsDead() || IsHealthFull()) return false;
    SetHealth(Health + HealthAmount);
    return true;
}

bool URaGHealthComponent::IsHealthFull() const
{
    return FMath::IsNearlyEqual(Health, MaxHealth);
}

void URaGHealthComponent::BeginPlay()
{
	Super::BeginPlay();

    check(MaxHealth > 0);
    SetHealth(MaxHealth);


    AActor* ComponentOwner = GetOwner();
    if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &URaGHealthComponent::OnTakeAnyDamage);
    }

}
void URaGHealthComponent::OnTakeAnyDamage(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    if (Damage <= 0.0f || IsDead() || !GetWorld()) return;
    SetHealth(Health - Damage);

    GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);

    if (IsDead())
    {
        OnDeath.Broadcast();
    }
    else if (AutoHeal)
    {
        GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &URaGHealthComponent::HealUpdate, HealUpdateTime, true, HealDelay);
        
    }

}

void URaGHealthComponent::HealUpdate() {

    SetHealth(Health + HealModifier);

    if (IsHealthFull() && GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
    }
}

void URaGHealthComponent::SetHealth(float NewHealth) {

    Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(Health);
}
