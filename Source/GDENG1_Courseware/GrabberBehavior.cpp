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
	inputComponent->BindAction("Grab", EInputEvent::IE_Released, this, &UGrabberBehavior::Release);
	inputComponent->BindAction("Throw", EInputEvent::IE_Pressed, this, &UGrabberBehavior::Throw);

}


// Called every frame
void UGrabberBehavior::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (this->hasGrabbed) {
		//get player view point
		FVector location;
		FRotator rotation;
		this->GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(out location, out rotation);
		FVector lineTraceEnd = location + rotation.Vector() * REACH;

		if (this->grabbedActor != NULL) {

			if (this->physicsHandle != NULL) {
				this->physicsHandle->SetTargetLocation(lineTraceEnd);
			}
			else {
				//fallback
				UE_LOG(LogTemp, Display, TEXT("Physics handle missing. Using fallback!"));
				FVector grabbedLoc = this->grabbedActor->GetActorLocation();
				grabbedLoc = lineTraceEnd;
				grabbedActor->SetActorLocation(grabbedLoc);
			}
		}
	}
}


/*if (this->hasThrown) {
	this->hasThrown = false;
	this->primitiveComp->AddForce(FVector(0.0, 0.0, 10000.0f));
}*/

void UGrabberBehavior::Grab()
{
	//get player view point
	FVector location;
	FRotator rotation;
	this->GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(out location, out rotation);

	//perform line tracing
	FVector lineTraceEnd = location + rotation.Vector() * REACH;
	DrawDebugLine(this->GetWorld(), location, lineTraceEnd, FColor::Red, false, 0.0, 0, 5.0f);

	//raycast to a certain distance
	FHitResult hitResult;
	FCollisionQueryParams traceParams(FName(TEXT("myQuery")), false, this->GetOwner()); //params for line tracing
	this->GetWorld()->LineTraceSingleByObjectType(out hitResult, location, lineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), traceParams);
	this->grabbedActor = hitResult.GetActor();
	if (this->grabbedActor != NULL) {
		this->hasGrabbed = true;
		this->primitiveComp = hitResult.GetComponent();
		UE_LOG(LogTemp, Display, TEXT("Grabbed! %s"), *this->grabbedActor->GetName());

		//using physics handle component
		this->physicsHandle = this->grabbedActor->FindComponentByClass<UPhysicsHandleComponent>();
		if (this->physicsHandle != NULL) {
			//denotes the origin
			this->physicsHandle->GrabComponentAtLocation(this->primitiveComp, EName::NAME_None, lineTraceEnd);
		}
	}	
}

void UGrabberBehavior::Release()
{
	UE_LOG(LogTemp, Display, TEXT("Released!"));
	this->hasGrabbed = false;
	this->grabbedActor = NULL;

	if (this->physicsHandle != NULL) {
		this->physicsHandle->ReleaseComponent();
	}
}

void UGrabberBehavior::Throw()
{
	UE_LOG(LogTemp, Display, TEXT("Throw!"));
	this->hasThrown = true;
}

