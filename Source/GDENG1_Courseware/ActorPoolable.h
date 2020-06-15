// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMeshActor.h"
#include "ActorPoolable.generated.h"

UCLASS()
class GDENG1_COURSEWARE_API AActorPoolable : public AStaticMeshActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorPoolable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnInitialize(); //initializes the property of this object.
	virtual void OnRelease(); //throws this event when this object has been released back to the pool.
	virtual void OnActivate(); //throws this event when this object has been activated from the pool.

};
