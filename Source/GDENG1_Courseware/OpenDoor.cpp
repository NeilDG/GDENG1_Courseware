// COPYRIGHT: Neil Del Gallego


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"


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
	//this->targetYaw = this->initialYaw + 90.0f;
	//this->openingYaw += this->initialYaw;

	//assign actor automatically
	this->actorOpener = this->GetWorld()->GetFirstPlayerController()->GetPawn();

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
	if (this->actorOpener != NULL && this->pressurePlate->IsOverlappingActor(this->actorOpener) && this->doorState == CLOSED) {
		this->ticks = 0.0f;
		this->doorState = OPEN;
	}
	else if (this->doorState == OPEN) {
		this->doorState = CLOSED;
	}

	this->ticks += DeltaTime;
	//UE_LOG(LogTemp, Display, TEXT("Ticks: %f"), this->ticks);

	if (this->doorState == OPEN) {
		this->currentYaw = FMath::Lerp(this->currentYaw, this->openingYaw, DeltaTime * 1.0f);

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

