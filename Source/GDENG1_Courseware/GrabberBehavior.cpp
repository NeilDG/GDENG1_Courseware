// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GrabberBehavior.h"
#include "DrawDebugHelpers.h"

#define out

// Sets default values for this component's properties
UGrabberBehavior::UGrabberBehavior()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabberBehavior::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty %s"), *this->GetOwner()->FindComponentByClass<UGrabberBehavior>()->GetName());

	UInputComponent* inputComponent = this->GetOwner()->FindComponentByClass<UInputComponent>();
	inputComponent->BindAction("Grab", EInputEvent::IE_Pressed, this, &UGrabberBehavior::Grab);
}


// Called every frame
void UGrabberBehavior::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	//get player view point
	FVector location;
	FRotator rotation;
	this->GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(out location, out rotation);

	//UE_LOG(LogTemp, Warning, TEXT("Location: %s   Rotation: %s"), *location.ToString(), *rotation.ToString());

	//perform line tracing
	FVector lineTraceEnd = location + rotation.Vector() * REACH;
	DrawDebugLine(this->GetWorld(), location, lineTraceEnd, FColor::Red, false, 0.0, 0, 5.0f);

	//raycast to a certain distance
	FHitResult hitResult;
	FCollisionQueryParams traceParams(FName(TEXT("myQuery")), false, this->GetOwner()); //params for line tracing
	this->GetWorld()->LineTraceSingleByObjectType(out hitResult, location, lineTraceEnd, 
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), traceParams);

	if (hitResult.GetActor() != NULL) {
		UE_LOG(LogTemp, Warning, TEXT("Hit name: %s"), *hitResult.GetActor()->GetName());
	}
	
}

void UGrabberBehavior::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabbed!"));
}

