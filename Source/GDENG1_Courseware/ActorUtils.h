// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"

/**
 * 
 */
class GDENG1_COURSEWARE_API ActorUtils
{
public:
	ActorUtils();
	~ActorUtils();
	
	static void SetEnabled(AActor* actor, bool flag);
};
