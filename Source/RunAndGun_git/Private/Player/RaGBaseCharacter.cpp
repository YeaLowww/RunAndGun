// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RaGBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/RaGCharacterMovementComponent.h"
#include "Components/RaGHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/RaGWeaponComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/Controller.h"
#include "Components/CapsuleComponent.h"

DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog, All, All)


ARaGBaseCharacter::ARaGBaseCharacter(const FObjectInitializer& ObjInit)
    :Super(ObjInit.SetDefaultSubobjectClass<URaGCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;
    SpringArmComponent->SocketOffset = FVector(0.0f, 100.0f, 80.0f);

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);

    HealthComponent = CreateDefaultSubobject<URaGHealthComponent>("HealthComponent");

    HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
    HealthTextComponent->SetupAttachment(GetRootComponent());
    HealthTextComponent->SetOwnerNoSee(true);

    WeaponComponent = CreateDefaultSubobject<URaGWeaponComponent>("WeaponComponent");
}

void ARaGBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
    check(HealthTextComponent);
    check(HealthComponent);
    check(GetCharacterMovement());
    check(GetMesh());

    OnHealthChanged(HealthComponent->GetHealth(), 0.0f);
    HealthComponent->OnDeath.AddUObject(this, &ARaGBaseCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &ARaGBaseCharacter::OnHealthChanged);

    LandedDelegate.AddDynamic(this, &ARaGBaseCharacter::OnGroundLanded);

}

void ARaGBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ARaGBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    check(PlayerInputComponent);
    check(WeaponComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ARaGBaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ARaGBaseCharacter::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &ARaGBaseCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnAround", this, &ARaGBaseCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ARaGBaseCharacter::Jump);
    PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ARaGBaseCharacter::OnStartRunning);
    PlayerInputComponent->BindAction("Run", IE_Released, this, &ARaGBaseCharacter::OnStopRunning);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &URaGWeaponComponent::StartFire);
    PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &URaGWeaponComponent::StopFire);
    PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &URaGWeaponComponent::NextWeapon);
    PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &URaGWeaponComponent::Reload);
}


void ARaGBaseCharacter::MoveForward(float Amount) {

    IsMovingForward = Amount > 0.0f;
    if (Amount == 0.0f) return;
	AddMovementInput(GetActorForwardVector(), Amount);

    
}
void ARaGBaseCharacter::MoveRight(float Amount) {
    if (Amount == 0.0f) return;
	AddMovementInput(GetActorRightVector(), Amount);

}
void ARaGBaseCharacter::OnStartRunning() {
    WantsToRun = true;
}
void ARaGBaseCharacter::OnStopRunning() {
    WantsToRun = false;
}


bool ARaGBaseCharacter::isRunning() const
{
    return WantsToRun && IsMovingForward && !GetVelocity().IsZero();
    
}

float ARaGBaseCharacter::GetMovementDirection() const
{
    if (GetVelocity().IsZero()) return 0.0f;
    const auto VelocityNormal = GetVelocity().GetSafeNormal();
    const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
    const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
    const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
    return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void ARaGBaseCharacter::OnDeath() {

    UE_LOG(BaseCharacterLog, Display, TEXT("Character is DEAD %s"), *GetName());

    //PlayAnimMontage(DeathAnimMontage);

    GetCharacterMovement()->DisableMovement();

    SetLifeSpan(LifeSpanOnDeath);
    if (Controller)
    {
        Controller->ChangeState(NAME_Spectating);
    }
    GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

    WeaponComponent->StopFire();

    GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GetMesh()->SetSimulatePhysics(true);
}

void ARaGBaseCharacter::OnHealthChanged(float Health, float HealthDelta)
{
    HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));

}

void ARaGBaseCharacter::OnGroundLanded(const FHitResult& Hit) {

    const auto FallVelocityZ = -GetVelocity().Z;
    UE_LOG(BaseCharacterLog, Display, TEXT("Character on Landed %f"), FallVelocityZ);

    if (FallVelocityZ < LandedDamageVelocity.X) return;

    const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
    UE_LOG(BaseCharacterLog, Display, TEXT("FinalDamage %f"), FinalDamage);
    TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
}


