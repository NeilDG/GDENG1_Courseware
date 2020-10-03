// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DestructibleComponent.h"
#include "DestructionEvent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GDENG1_COURSEWARE_API UDestructionEvent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDestructionEvent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable) void OnFracture(const FVector& HitPoint, const FVector& HitDirection);

private:
	UPROPERTY(EditAnywhere) AActor* itemCopy;
	bool triggered;
	static void SetEnabled(AActor* actor, bool flag);
};
