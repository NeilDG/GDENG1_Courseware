// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Array.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "MultipleSpawner.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GDENG1_COURSEWARE_API UMultipleSpawner : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMultipleSpawner();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	UPROPERTY(EditAnywhere) TArray<AActor*> spawnLocations;
	UPROPERTY(EditAnywhere) TArray<AActor*> possibleObjects;

	AActor* activeObject;
	int spawnIndex = 0;
	int itemIndex = 0;

	float ticks = 0.0;
	const float SPAWN_INTERVAL = 1.0f;

	void DelaySpawn();
	
};
