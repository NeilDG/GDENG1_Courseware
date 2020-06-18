// Fill out your copyright notice in the Description page of Project Settings.



#include "MultipleSpawner.h"
#include "ActorUtils.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMultipleSpawner::UMultipleSpawner()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMultipleSpawner::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < this->spawnLocations.Num(); i++) {
		ActorUtils::SetEnabled(this->spawnLocations[i], false);
	}

	for (int i = 0; i < this->possibleObjects.Num(); i++) {
		ActorUtils::SetEnabled(this->possibleObjects[i], false);
	}
	
	//alternative: use delay(). This is similar to Coroutine function from Unity. NOTE: NOT WORKING SO FAR.
	/*FLatentActionInfo funcInfo;
	funcInfo.ExecutionFunction = "DelaySpawn";
	UKismetSystemLibrary::Delay(this, 2.0f, funcInfo);*/
}


// Called every frame
void UMultipleSpawner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	this->ticks += DeltaTime;
	if (this->ticks > this->SPAWN_INTERVAL) {
		this->ticks = 0.0f;
		this->DelaySpawn();
	}

	
}

void UMultipleSpawner::DelaySpawn()
{
	this->spawnIndex = (this->spawnIndex + 1) % this->spawnLocations.Num();
	this->itemIndex = FMath::RandRange(0, this->possibleObjects.Num() - 1);

	if (this->activeObject != NULL) {
		this->GetWorld()->DestroyActor(this->activeObject);
		this->activeObject = NULL;
	}
	FActorSpawnParameters spawnParams;
	spawnParams.Template = this->possibleObjects[this->itemIndex];
	spawnParams.Owner = this->GetOwner();

	this->activeObject = this->GetWorld()->SpawnActor<AActor>(spawnParams.Template->GetClass(), spawnParams.Template->GetActorTransform(), spawnParams);
	this->activeObject->AttachToActor(this->GetOwner(), FAttachmentTransformRules::KeepRelativeTransform);

	FVector location = this->spawnLocations[this->spawnIndex]->GetActorLocation();
	location.Z = spawnParams.Template->GetActorLocation().Z; //retain Z axis
	FRotator rotation = this->spawnLocations[this->spawnIndex]->GetActorRotation();
	this->activeObject->SetActorLocationAndRotation(location, rotation);
	ActorUtils::SetEnabled(this->activeObject, true);
}

