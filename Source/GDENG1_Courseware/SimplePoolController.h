// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/EngineTypes.h"
#include "ObjectPool.h"
#include "Math/UnrealMathUtility.h"
#include "SimplePoolController.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GDENG1_COURSEWARE_API USimplePoolController : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USimplePoolController();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere) AActor* objectPoolActor; //seems to be the best way to access some components from other objects
	UObjectPool* objectPool;

	float ticks = 0.0;
	float SPAWN_INTERVAL = FMath::RandRange(1.0f, 4.0f);

	float releaseTicks = 0.0f;
	float RELEASE_INTERVAL = 2.0f;
		
};
