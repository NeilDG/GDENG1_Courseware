// COPYRIGHT: Neil Del Gallego


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	this->initialYaw = this->GetOwner()->GetActorRotation().Yaw;
	this->currentYaw = this->initialYaw;
	this->openingYaw += this->initialYaw;

	//assign actor automatically
	//this->actorOpener = this->GetWorld()->GetFirstPlayerController()->GetPawn();

}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/*
	this->ticks += DeltaTime;
	FRotator currentRot = this->GetOwner()->GetActorRotation();
	//UE_LOG(LogTemp, Display, TEXT("Current Rot %f"), currentRot.Yaw);

	if (currentRot.Yaw <= 90.0f) {
		currentRot.Yaw += 10.0f * DeltaTime;
		this->GetOwner()->SetActorRotation(currentRot);
	}
	*/

	//open door
	//UE_LOG(LogTemp, Display, TEXT("Total mass: %f"), this->GetTotalMass());
	if (this->GetTotalMass() >= this->totalMass && this->doorState == CLOSED) {
		this->ticks = 0.0f;
		this->doorState = OPEN;
	}
	/*if (this->actorOpener != NULL && this->pressurePlate->IsOverlappingActor(this->actorOpener) && this->doorState == CLOSED) {
		this->ticks = 0.0f;
		this->doorState = OPEN;
	}
	else if (this->alternativeOpener != NULL && this->pressurePlate->IsOverlappingActor(this->alternativeOpener) && this->doorState == CLOSED) {
		//IMPORTANT: Actor must have generate overlap event set to true in collision componennts
		this->ticks = 0.0f;
		this->doorState = OPEN;
		UE_LOG(LogTemp, Display, TEXT("Using cube opener!"));
	}*/
	else if (this->GetTotalMass() < this->totalMass && this->doorState == OPEN) {
		this->doorState = CLOSED;
	}

	this->ticks += DeltaTime;
	//UE_LOG(LogTemp, Display, TEXT("Ticks: %f"), this->ticks);

	if (this->doorState == OPEN) {
		this->currentYaw = FMath::Lerp(this->currentYaw, this->openingYaw, DeltaTime * 3.0f);

		FRotator doorRot = this->GetOwner()->GetActorRotation();
		doorRot.Yaw = this->currentYaw;
		this->GetOwner()->SetActorRotation(doorRot);
	}
	else if (this->doorState == CLOSED && this->ticks > 2.0f) {
		//close door if 2 seconds passed
		this->currentYaw = FMath::Lerp(this->currentYaw, this->closingYaw, DeltaTime * 1.0f);
		FRotator doorRot = this->GetOwner()->GetActorRotation();
		doorRot.Yaw = this->currentYaw;
		this->GetOwner()->SetActorRotation(doorRot);
	}

}

float UOpenDoor::GetTotalMass() const
{
	TArray<AActor*> actors;
	this->pressurePlate->GetOverlappingActors(actors);
	
	float mass = 0.0f;
	for (int i = 0; i < actors.Num(); i++) {
		UPrimitiveComponent* primitive = actors[i]->FindComponentByClass<UPrimitiveComponent>();
		mass += primitive->GetMass();
	}
	return mass;
}

