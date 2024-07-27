// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RaGBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/RaGCharacterMovementComponent.h"
#include "Components/RaGHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "Engine/DamageEvents.h"


DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog, All, All);

// Sets default values
ARaGBaseCharacter::ARaGBaseCharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<URaGCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);

    HealthComponent = CreateDefaultSubobject<URaGHealthComponent>("HealthComponent");

    HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
    HealthTextComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ARaGBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
    check(HealthTextComponent);
    check(HealthComponent);
   
}

// Called every frame
void ARaGBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    const auto Health = HealthComponent->GetHealth();
    HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));

}




// Called to bind functionality to input
void ARaGBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ARaGBaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ARaGBaseCharacter::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &ARaGBaseCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnAround", this, &ARaGBaseCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ARaGBaseCharacter::Jump);
    PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ARaGBaseCharacter::OnStartRunning);
    PlayerInputComponent->BindAction("Run", IE_Released, this, &ARaGBaseCharacter::OnStopRunning);
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

