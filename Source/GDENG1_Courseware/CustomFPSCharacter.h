// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FP_FirstPerson/FP_FirstPersonCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "ItemData.h"
#include "CustomFPSCharacter.generated.h"

/**
 * 
 */
UCLASS()
class GDENG1_COURSEWARE_API ACustomFPSCharacter : public AFP_FirstPersonCharacter
{
	GENERATED_BODY()
public:
	ACustomFPSCharacter();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void OnFire() override;
	UPROPERTY(BlueprintReadWrite) AActor* projectileCopy;
	UPROPERTY(BlueprintReadWrite) FVector projectileSpawnPos;

private:
	ItemData* activeItem;
};
