// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInventoryManager.h"

APlayerInventoryManager* APlayerInventoryManager::sharedInstance = nullptr;
APlayerInventoryManager* APlayerInventoryManager::GetSharedInstance()
{
	return sharedInstance;
}

// Sets default values
APlayerInventoryManager::APlayerInventoryManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlayerInventoryManager::BeginPlay()
{
	Super::BeginPlay();
	sharedInstance = this;
	this->PopulateItems();
}

// Called every frame
void APlayerInventoryManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerInventoryManager::PopulateItems()
{
	this->itemList.Add(new ItemData("BasicBullet", 0.5f, 1.0f));
	this->itemList.Add(new ItemData("FastBullet", 0.15f, 2.0f));
	this->itemList.Add(new ItemData("BigBullet", 2.0f, 1.0f));
	this->itemList.Add(new ItemData("BFBullet", 4.0f, 2.0f));

	UE_LOG(LogTemp, Log, TEXT("[PlayerInventoryManager] Successfully populated items!"));
}

ItemData* APlayerInventoryManager::GetBulletData(int index)
{
	return this->itemList[index];
}

ItemData* APlayerInventoryManager::GetActiveBullet()
{
	return this->GetBulletData(this->activeIndex);
}

void APlayerInventoryManager::SetActiveIndex(int index)
{
	this->activeIndex = index;
}

int APlayerInventoryManager::GetRandomItemIndex() const
{
	const int index = FMath::RandRange(0, this->itemList.Num() - 1);
	return index;
}

