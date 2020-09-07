// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController_2.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

void ATankPlayerController_2::BeginPlay()
{
	Super::BeginPlay();

	UInputComponent* inputComponent = this->FindComponentByClass<UInputComponent>();
	inputComponent->BindAction("Grab", EInputEvent::IE_Pressed, this, &ATankPlayerController_2::OnFire);
	inputComponent->BindAxis("MoveX", this, &ATankPlayerController_2::OnMove);
}

void ATankPlayerController_2::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

ATankPawn_2* ATankPlayerController_2::GetControlledTank() const
{
	return this->GetPawn<ATankPawn_2>();
}

bool ATankPlayerController_2::GetRayHitLocation()
{
	bool hasHit = this->DeprojectScreenPositionToWorld(this->crosshairScreenLoc.X, this->crosshairScreenLoc.Y, this->latestCameraLoc, this->latestWorldDirection);
	return hasHit;
}

bool ATankPlayerController_2::GetWorldPoint()
{
	FHitResult hitResult;
	FVector startLoc = this->latestCameraLoc; //Alternative: PlayerCameraManager->GetCameraLocation();
	FVector endLoc = startLoc + (this->latestWorldDirection * 50000000.0f);

	bool result = this->GetWorld()->LineTraceSingleByChannel(hitResult, startLoc, endLoc, ECollisionChannel::ECC_Visibility);
	DrawDebugLine(this->GetWorld(), startLoc, endLoc, FColor::Red, false, 0.15, 0, 5.0f);
	this->latestWorldPoint = hitResult.Location;
	this->latestWorldPoint.Z += 100.0f; //add offset
	return result;
}

//to be called by fire button.
void ATankPlayerController_2::OnFire()
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

void ATankPlayerController_2::OnMove(float axis)
{
	this->GetControlledTank()->Move(axis);
}
