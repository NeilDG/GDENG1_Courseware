// Fill out your copyright notice in the Description page of Project Settings.


#include "CrowdSpawner.h"
#include "Engine/World.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/StaticMesh.h"
#include "Math/UnrealMathUtility.h"
#include "UObject/UObjectGlobals.h"

// Sets default values for this component's properties
UCrowdSpawner::UCrowdSpawner()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCrowdSpawner::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCrowdSpawner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	this->ticks += DeltaTime;
	if (this->ticks > this->INTERVAL) {
		this->SpawnNActors();
		this->ticks = 0.0f;
	}
}

void UCrowdSpawner::SpawnNActors() const
{
	UE_LOG(LogTemp, Display, TEXT("Time to spawn!"));
	if (this->crowdActor != NULL) {
		FActorSpawnParameters spawnParams;
		spawnParams.Template = this->crowdActor;
		spawnParams.Owner = this->GetOwner();

		FVector location = this->crowdActor->GetActorLocation();
		FRotator rotator = this->crowdActor->GetActorRotation();

		AStaticMeshActor* spawn = (AStaticMeshActor*)this->GetWorld()->SpawnActor(this->crowdActor->GetClass(), &location, &rotator, spawnParams);
	}
}

