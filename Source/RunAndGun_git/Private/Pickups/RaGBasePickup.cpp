

#include "Pickups/RaGBasePickup.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickups, All, All);

ARaGBasePickup::ARaGBasePickup()
{
    PrimaryActorTick.bCanEverTick = true;

    PrimaryActorTick.bCanEverTick = false;
    CollisionComponent = CreateDefaultSubobject<USphereComponent>("CollisionComponent");
    CollisionComponent->InitSphereRadius(50.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    SetRootComponent(CollisionComponent);
}

void ARaGBasePickup::BeginPlay()
{
    Super::BeginPlay();
    check(CollisionComponent);
    GenerateRotationYaw();
}

void ARaGBasePickup::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    AddActorLocalRotation(FRotator(0.0f, RotationYaw, 0.0f));
}

void ARaGBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    const auto Pawn = Cast<APawn>(OtherActor);
    if (GivePickupTo(Pawn))
    {
        PickupWasTaken();
    }
}

bool ARaGBasePickup::GivePickupTo(APawn* PlayerPawn)
{
    return false;
}

void ARaGBasePickup::PickupWasTaken()
{

    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    if (GetRootComponent())
    {

        GetRootComponent()->SetVisibility(false, true);
    }

    FTimerHandle RespawnTimerHandle;
    GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ARaGBasePickup::Respawn, RespawnTime);
}

void ARaGBasePickup::Respawn() {
    GenerateRotationYaw();
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    if (GetRootComponent())
    {

        GetRootComponent()->SetVisibility(true, true);
    }
}

void ARaGBasePickup::GenerateRotationYaw() {
    const auto Direction = FMath::RandBool() ? 1.0f : -1.0f;  
    RotationYaw = FMath::RandRange(1.0f, 2.0f) * Direction;
}
