// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankPawn.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class GDENG1_COURSEWARE_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite) AActor* actorCopy;

private:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	ATankPawn* GetControlledTank() const;
	ATankPawn* GetPlayerTank() const;

	bool GetWorldPoint();
	void OnFire();

	FVector latestWorldDirection;
	FVector latestWorldPoint;
	float fireTicks = 0.0f;
	float FIRE_INTERVAL = 1.0f;
};
