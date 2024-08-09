// Fill out your copyright notice in the Description page of Project Settings.

#include "Animation/RaGEquipFinishedAnimNotify.h"

void URaGEquipFinishedAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) {
    OnNotified.Broadcast(MeshComp);
    Super::Notify(MeshComp, Animation);

}
