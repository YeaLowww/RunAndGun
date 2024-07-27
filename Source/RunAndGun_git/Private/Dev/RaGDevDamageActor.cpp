// Fill out your copyright notice in the Description page of Project Settings.


#include "Dev/RaGDevDamageActor.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"


ARaGDevDamageActor::ARaGDevDamageActor()
{
 	
	PrimaryActorTick.bCanEverTick = true;
    SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
    SetRootComponent(SceneComponent);
}

void ARaGDevDamageActor::BeginPlay()
{
	Super::BeginPlay();
	
}


void ARaGDevDamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 24, SphereColor);
    UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), Radius, DamageType, {}, this, nullptr, DoFullDamage);
}

