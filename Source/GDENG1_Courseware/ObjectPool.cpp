// Fill out your copyright notice in the Description page of Project Settings.


#include "Engine/World.h"
#include "ObjectPool.h"

// Sets default values for this component's properties
UObjectPool::UObjectPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UObjectPool::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UObjectPool::BeginDestroy()
{
	Super::BeginDestroy(); //IMPORTANT: Any lifecycle events must have super function. Or else Unreal Engine will crash.
}



// Called every frame
void UObjectPool::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UObjectPool::Initialize()
{
	if (this->actorCopy == NULL) {
		UE_LOG(LogTemp, Display, TEXT("Actor is null. Object pool not initialized."));
		return;
	}
	
	UE_LOG(LogTemp, Display, TEXT("Actor is %s"), *this->actorCopy->GetName());

	//disable per-update functions
	

	FActorSpawnParameters spawnParams;
	spawnParams.Template = this->actorCopy;
	spawnParams.Owner = this->GetOwner();

	const FTransform transform = this->actorCopy->GetActorTransform();
	for (int i = 0; i < this->maxPoolSize - 1; i++) {
		AActorPoolable* poolableObject = this->GetWorld()->SpawnActor<AActorPoolable>(this->actorCopy->GetClass(), spawnParams);
		poolableObject->SetIndex(i);
		poolableObject->OnInitialize();
		this->availableObjects.Push(poolableObject);
	}
}

bool UObjectPool::HasObjectAvailable(int requestSize)
{
	return this->availableObjects.Num() > 0;
}

AActorPoolable* UObjectPool::RequestPoolable()
{
	if (this->HasObjectAvailable(1)) {
		AActorPoolable* object = this->availableObjects.Pop();
		object->SetIndex(this->usedObjects.Num());
		this->usedObjects.Push(object);
		object->SetActorTransform(this->GetOwner()->GetActorTransform());
		object->OnActivate();
		UE_LOG(LogTemp, Display, TEXT("Finished spawning %s"), *object->GetName());
		return object;
	}
	else {
		UE_LOG(LogTemp, Display, TEXT("No more available objects."));
		return NULL;
	}
	
}

TArray<AActorPoolable*> UObjectPool::RequestPoolableBatch(int size)
{
	TArray<AActorPoolable*> objects;
	for (int i = 0; i < size && this->availableObjects.Num() > 0; i++) {
		objects.Push(this->RequestPoolable());
	}

	return objects;
}

void UObjectPool::ReleasePoolable(AActorPoolable* poolableObject)
{
	poolableObject->OnRelease();
	this->usedObjects.Remove(poolableObject);
	this->availableObjects.Push(poolableObject);
}

void UObjectPool::ReleasePoolableBatch(TArray<AActorPoolable*> objectList)
{
	for (int i = 0; i < objectList.Num(); i++) {
		this->ReleasePoolable(objectList[i]);
	}
}

void UObjectPool::ReleasePoolableBatch(int count)
{
	TArray<AActorPoolable*> toRemove;
	for (int i = 0; i < this->usedObjects.Num() && i < count; i++) {
		toRemove.Push(this->usedObjects[i]);
	}

	
	this->ReleasePoolableBatch(toRemove);
}

