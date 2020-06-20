// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankPawn_2.generated.h"

UCLASS()
class GDENG1_COURSEWARE_API ATankPawn_2 : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATankPawn_2();
	void Move(float throttleSpeed);
	void Sideways(float throttleSpeed);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadWrite) UStaticMeshComponent* leftTrack;
	UPROPERTY(BlueprintReadWrite) UStaticMeshComponent* rightTrack;
	UPROPERTY(BlueprintReadWrite) UPrimitiveComponent* tankBody;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	const float TRACK_STRENGTH = 1250.0f;
};
