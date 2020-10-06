// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickableActor.generated.h"

UCLASS()
class GDENG1_COURSEWARE_API APickableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickableActor();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintImplementableEvent) void OnItemSetup();
	void SetActorParent(AActor* parent);
	void SetItemIndex(int index);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable) void SetOverlap(AActor* overlappingActor, bool flag);
	UPROPERTY(BlueprintReadOnly) int itemIndex = 0;

private:
	AActor* destructibleOwner;
	AActor* actorOverlap;
	bool hasOverlap = false;
};
