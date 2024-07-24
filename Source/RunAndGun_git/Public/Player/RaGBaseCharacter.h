// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RaGBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
UCLASS()
class RUNANDGUN_GIT_API ARaGBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	ARaGBaseCharacter();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;
	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
    void MoveForward(float Amount);
	void MoveRight(float Amount);

};
