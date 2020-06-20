// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankPawn_2.h"
#include "TankAIController_2.generated.h"

/**
 * 
 */
UCLASS()
class GDENG1_COURSEWARE_API ATankAIController_2 : public AAIController
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite) AActor* actorCopy;

private:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	ATankPawn_2* GetControlledTank() const;
	ATankPawn_2* GetPlayerTank() const;

	bool GetWorldPoint();
	void OnFire();

	FVector latestWorldPoint;
	float fireTicks = 0.0f;
	float FIRE_INTERVAL = 1.0f;
};
