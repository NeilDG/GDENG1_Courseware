// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankPawn.h"
#include "CoreMinimal.h"
#include "Components/Image.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"
/**
 * 
 */
UCLASS()
class GDENG1_COURSEWARE_API ATankPlayerController : public APlayerController
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

	ATankPawn* GetControlledTank() const;
	bool GetRayHitLocation();
	bool GetWorldPoint();
	void OnFire();
	void OnMove(float axis);
	void OnSideways(float axis);
};
