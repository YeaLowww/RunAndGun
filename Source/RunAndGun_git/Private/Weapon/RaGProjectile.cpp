

#include "Weapon/RaGProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/Components/RaGWeaponFXComponent.h"

ARaGProjectile::ARaGProjectile()
{

    PrimaryActorTick.bCanEverTick = false;
    CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
    CollisionComponent->InitSphereRadius(5.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    CollisionComponent->bReturnMaterialOnMove = true;
    SetRootComponent(CollisionComponent);

    MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
    MovementComponent->InitialSpeed = 2000.0f;
    MovementComponent->ProjectileGravityScale = 0.0f;

    WeaponFXComponent = CreateDefaultSubobject<URaGWeaponFXComponent>("WeaponFXComponent");
}

void ARaGProjectile::BeginPlay()
{
    Super::BeginPlay();

    check(MovementComponent);
    check(CollisionComponent);
    check(WeaponFXComponent);
    MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;

    CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
    CollisionComponent->OnComponentHit.AddDynamic(this, &ARaGProjectile::OnProjectileHit);
    SetLifeSpan(LifeSeconds);
}

void ARaGProjectile::OnProjectileHit(
    UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (!GetWorld()) return;

    MovementComponent->StopMovementImmediately();

    // make damage
    UGameplayStatics::ApplyRadialDamage(GetWorld(), DamageAmount,  //
        GetActorLocation(),                                        //
        DamageRadius,                                              //
        UDamageType::StaticClass(),                                //
        {GetOwner()},                                              //
        this,                                                      //
        GetController(),                                           //
        DoFullDamage);                                             //

    //DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 24, FColor::Red, false, 5.0f);

    WeaponFXComponent->PlayImpactFX(Hit);
    Destroy();
}

AController* ARaGProjectile::GetController() const
{
    const auto Pawn = Cast<APawn>(GetOwner());
    
    return Pawn ? Pawn->GetController() : nullptr;
}
