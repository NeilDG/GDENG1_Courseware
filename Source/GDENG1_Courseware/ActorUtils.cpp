// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorUtils.h"

ActorUtils::ActorUtils()
{
}

ActorUtils::~ActorUtils()
{
}

void ActorUtils::SetEnabled(AActor* actor, bool flag)
{
	actor->SetActorHiddenInGame(!flag);
	actor->SetActorTickEnabled(flag);
	/*UPrimitiveComponent* primitive = actor->FindComponentByClass<UPrimitiveComponent>();
	if (primitive->Mobility == EComponentMobility::Movable) {
		primitive->SetSimulatePhysics(flag);
	}*/
}
