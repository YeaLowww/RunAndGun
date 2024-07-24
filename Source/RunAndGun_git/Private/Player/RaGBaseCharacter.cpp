// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RaGBaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
// Sets default values
ARaGBaseCharacter::ARaGBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void ARaGBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
    
	
}

// Called every frame
void ARaGBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
}

// Called to bind functionality to input
void ARaGBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ARaGBaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ARaGBaseCharacter::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &ARaGBaseCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnAround", this, &ARaGBaseCharacter::AddControllerYawInput);
}

void ARaGBaseCharacter::MoveForward(float Amount) {

	AddMovementInput(GetActorForwardVector(), Amount);

}

void ARaGBaseCharacter::MoveRight(float Amount) {

	AddMovementInput(GetActorRightVector(), Amount);

}



