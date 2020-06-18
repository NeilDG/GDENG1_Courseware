// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankPawn.h"
#include "CoreMinimal.h"
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

public:
	ATankPawn* GetControlledTank() const;
};
