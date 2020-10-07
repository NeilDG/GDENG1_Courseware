// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Containers/Array.h"
#include "ItemData.h"
#include "PlayerInventoryManager.generated.h"

UCLASS()
class GDENG1_COURSEWARE_API APlayerInventoryManager : public AActor
{
	GENERATED_BODY()
	
public:
	static APlayerInventoryManager* GetSharedInstance();
	static const int BASIC_BULLET_INDEX = 0;
	static const int FAST_BULLET_INDEX = 1;
	static const int BIG_BULLET_INDEX = 2;
	static const int BF_BULLET_INDEX = 3;
	
	// Sets default values for this actor's properties
	APlayerInventoryManager();
	ItemData* GetActiveBullet();
	void SetActiveIndex(int index);
	int GetRandomItemIndex() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	static APlayerInventoryManager* sharedInstance;
	TArray<ItemData*> itemList;

	int activeIndex = 0;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void PopulateItems();
	ItemData* GetBulletData(int index);
};
