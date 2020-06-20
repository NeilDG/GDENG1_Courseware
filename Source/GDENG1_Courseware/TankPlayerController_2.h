// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPawn_2.h"
#include "TankPlayerController_2.generated.h"

/**
 * 
 */
UCLASS()
class GDENG1_COURSEWARE_API ATankPlayerController_2 : public APlayerController
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override;
	UPROPERTY(BlueprintReadWrite) FVector2D crosshairScreenLoc;
	UPROPERTY(BlueprintReadWrite) AActor* actorCopy;

private:
	FVector latestCameraLoc;
	FVector latestWorldDirection;
	FVector latestWorldPoint;

	ATankPawn_2* GetControlledTank() const;

	bool GetRayHitLocation();
	bool GetWorldPoint();
	void OnFire();
};
