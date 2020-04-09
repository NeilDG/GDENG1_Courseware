// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SnowmanBlueprintFunctions.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GDENG1_COURSEWARE_API USnowmanBlueprintFunctions : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USnowmanBlueprintFunctions();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UFUNCTION(BlueprintCallable) void Move(bool alongX, bool alongY, float movementX, float movementY, float deltaTime);
	UPROPERTY(EditAnywhere) float SPEED_MULTIPLIER = 500.0f;
		
};
