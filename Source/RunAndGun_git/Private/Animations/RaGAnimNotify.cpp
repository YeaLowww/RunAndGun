// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/RaGAnimNotify.h"

void URaGAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    OnNotified.Broadcast(MeshComp);
    Super::Notify(MeshComp, Animation);
}