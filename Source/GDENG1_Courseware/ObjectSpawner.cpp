// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectSpawner.h"
#include "Engine/World.h"
#include "Components/SceneComponent.h"

// Sets default values for this component's properties
UObjectSpawner::UObjectSpawner()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UObjectSpawner::BeginPlay()
{
	Super::BeginPlay();

	// ...
	//this->actorCopy->SetHidden(true); //does not work because only variable bHidden is changed. Weird design.
	this->actorCopy->SetActorHiddenInGame(true);
	
}


// Called every frame
void UObjectSpawner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	this->ticks += DeltaTime;
	this->destroyTicks += DeltaTime;

	if (this->ticks > this->INTERVAL) {
		this->ticks = 0.0f;
		//spawn object
		if (this->actorCopy != NULL && this->spawnedObjects.Num() < this->spawnLimit) {
			FActorSpawnParameters spawnParams;
			spawnParams.Template = this->actorCopy;
			spawnParams.Owner = this->GetOwner();

			FVector spawnLocation = this->GetOwner()->GetActorLocation();
			FRotator spawnRotation = this->GetOwner()->GetActorRotation();
			

			AActor* myActor = this->GetWorld()->SpawnActor<AActor>(this->actorCopy->GetClass(), spawnParams);
			myActor->AttachToActor(this->GetOwner(), FAttachmentTransformRules::KeepRelativeTransform); //works but does not show hierarchy in outliner during gameplay.
			myActor->SetActorHiddenInGame(false);
			myActor->SetActorLocation(spawnLocation);
			myActor->SetActorRotation(spawnRotation);

			this->spawnedObjects.Add(myActor);
		}
		else {
			UE_LOG(LogTemp, Display, TEXT("Actor is null. Will not spawn."));
		}
		
	}

	if (this->destroyTicks > this->DELETE_INTERVAL) {
		this->destroyTicks = 0.0f;
		this->DeleteAll();
	}
}

void UObjectSpawner::DeleteAll()
{
	UE_LOG(LogTemp, Display, TEXT("Destroying all objects."));
	for (int i = 0; i < this->spawnedObjects.Num(); i++) {
		this->spawnedObjects[i]->Destroy();
	}
	this->spawnedObjects.Reset();
}

