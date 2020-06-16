// Fill out your copyright notice in the Description page of Project Settings.


#include "SimplePoolController.h"

// Sets default values for this component's properties
USimplePoolController::USimplePoolController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USimplePoolController::BeginPlay()
{
	Super::BeginPlay();
	if (this->objectPoolActor != NULL) {
		this->objectPool = this->objectPoolActor->FindComponentByClass<UObjectPool>();
		this->objectPool->Initialize();
	}
	
}


// Called every frame
void USimplePoolController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	this->ticks += DeltaTime;
	this->releaseTicks += DeltaTime;
	if (this->ticks > SPAWN_INTERVAL) {
		this->ticks = 0.0f;
		this->SPAWN_INTERVAL = FMath::RandRange(1.0f, 4.0f);
		int batchSize = FMath::RandRange(1, this->objectPool->GetMaxPoolSize()); //NOTE: Randrange is inclusive.
		this->objectPool->RequestPoolableBatch(batchSize);
	}

	if (this->releaseTicks > RELEASE_INTERVAL) {
		this->releaseTicks = 0.0f;
		this->RELEASE_INTERVAL = FMath::RandRange(1.0f, 4.0f);
		int batchSize = FMath::RandRange(1, this->objectPool->GetMaxPoolSize());
		UE_LOG(LogTemp, Display, TEXT("Releasing %d objects back to pool."), batchSize);
		this->objectPool->ReleasePoolableBatch(batchSize);
	}
}

