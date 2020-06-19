// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"


void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	ATankPawn* myPawn = this->GetControlledTank();

	if (myPawn != NULL) {
		UE_LOG(LogTemp, Display, TEXT("Player controller possessing %s"), *myPawn->GetName());
	}

	if (this->actorCopy != NULL) {
		this->actorCopy->SetActorHiddenInGame(true);
	}

	UInputComponent* inputComponent = this->FindComponentByClass<UInputComponent>();
	inputComponent->BindAction("Grab", EInputEvent::IE_Pressed, this, &ATankPlayerController::OnFire);
	inputComponent->BindAxis("MoveX", this, &ATankPlayerController::OnMove);
	inputComponent->BindAxis("MoveY", this, &ATankPlayerController::OnSideways);
}
void ATankPlayerController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}
ATankPawn* ATankPlayerController::GetControlledTank() const
{
	return this->GetPawn<ATankPawn>();
}

bool ATankPlayerController::GetRayHitLocation()
{
	bool hasHit = this->DeprojectScreenPositionToWorld(this->crosshairScreenLoc.X, this->crosshairScreenLoc.Y, this->latestCameraLoc, this->latestWorldDirection);
	return hasHit;
}

void ATankPlayerController::OnFire()
{
	bool hasHit = this->GetRayHitLocation();
	if (hasHit) {
		UE_LOG(LogTemp, Display, TEXT("Crosshair screen location: %s"), *this->crosshairScreenLoc.ToString());

		if (this->actorCopy != NULL && this->GetWorldPoint()) {
			FActorSpawnParameters spawnParams;
			spawnParams.Template = this->actorCopy;
			spawnParams.Owner = this->GetOwner();

			AActor* myActor = this->GetWorld()->SpawnActor<AActor>(this->actorCopy->GetClass(), spawnParams);
			myActor->AttachToActor(this->GetOwner(), FAttachmentTransformRules::KeepRelativeTransform); //works but does not show hierarchy in outliner during gameplay.
			myActor->SetActorHiddenInGame(false);
			myActor->SetActorLocation(this->latestWorldPoint);
			myActor->SetActorRotation(this->actorCopy->GetActorRotation());

			UE_LOG(LogTemp, Display, TEXT("Firing on: %s"), *this->latestWorldPoint.ToString());
		}
		
	}
	else {
		UE_LOG(LogTemp, Display, TEXT("No available target!"));
	}
	
}

void ATankPlayerController::OnMove(float axis)
{
	this->GetPawn<ATankPawn>()->Move(axis);
}

void ATankPlayerController::OnSideways(float axis)
{
	this->GetPawn<ATankPawn>()->Sideways(axis);
}

//performs ray tracing and hits the first valid object.
bool ATankPlayerController::GetWorldPoint() {
	FHitResult hitResult;
	FVector startLoc = this->latestCameraLoc; //Alternative: PlayerCameraManager->GetCameraLocation();
	FVector endLoc = startLoc + (this->latestWorldDirection * 50000000.0f);
	
	bool result = this->GetWorld()->LineTraceSingleByChannel(hitResult, startLoc, endLoc, ECollisionChannel::ECC_Visibility);
	//DrawDebugLine(this->GetWorld(), startLoc, endLoc, FColor::Red, false, 5.0, 0, 5.0f);
	this->latestWorldPoint = hitResult.Location;
	this->latestWorldPoint.Z += 100.0f; //add offset
	return result;
}
