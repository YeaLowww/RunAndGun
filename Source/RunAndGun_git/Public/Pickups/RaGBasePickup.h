
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RaGBasePickup.generated.h"

class USphereComponent;

UCLASS()
class RUNANDGUN_GIT_API ARaGBasePickup : public AActor
{
    GENERATED_BODY()

public:
    ARaGBasePickup();

protected:
    UPROPERTY(VisibleAnywhere, Category = "Pickups")
    USphereComponent* CollisionComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickups")
    float RespawnTime = 5.0f;

    virtual void BeginPlay() override;
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:
    virtual void Tick(float DeltaTime) override;
    bool CouldBeTaken() const;


private:
    float RotationYaw = 0.0f;
    virtual bool GivePickupTo(APawn* PlayerPawn);

    FTimerHandle RespawnTimerHandle;

    void PickupWasTaken();
    void Respawn();
    void GenerateRotationYaw();
};
