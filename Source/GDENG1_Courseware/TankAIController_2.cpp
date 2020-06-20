// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController_2.h"
#include "DrawDebugHelpers.h"

void ATankAIController_2::BeginPlay() {
	Super::BeginPlay();

	ATankPawn_2* myPawn = this->GetControlledTank();
	ATankPawn_2* myPlayer = this->GetPlayerTank();
	if (myPlayer != NULL && myPawn != NULL) {
		UE_LOG(LogTemp, Warning, TEXT("AI %s found player %s"), *myPawn->GetName(), *myPlayer->GetName());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Enemy tank or player tank is not assigned. Cancelling AI controller."));
	}

}

void ATankAIController_2::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	this->fireTicks += deltaTime;
	if (this->fireTicks > this->FIRE_INTERVAL) {
		this->FIRE_INTERVAL = FMath::FRandRange(0.25, 4.0f);
		this->fireTicks = 0.0f;
		this->OnFire();
	}
}

ATankPawn_2* ATankAIController_2::GetControlledTank() const
{
	return this->GetPawn<ATankPawn_2>();
}

ATankPawn_2* ATankAIController_2::GetPlayerTank() const
{
	ATankPawn_2* playerPawn = this->GetWorld()->GetFirstPlayerController()->GetPawn<ATankPawn_2>();
	return playerPawn;
}

bool ATankAIController_2::GetWorldPoint()
{
	FHitResult hitResult;
	FVector startLoc = this->GetControlledTank()->GetActorLocation();
	FVector endLoc = this->GetPlayerTank()->GetActorLocation();

	bool result = this->GetWorld()->LineTraceSingleByChannel(hitResult, startLoc, endLoc, ECollisionChannel::ECC_WorldDynamic);
	DrawDebugLine(this->GetWorld(), startLoc, endLoc, FColor::Red, false, 1.0, 0, 5.0f);
	this->latestWorldPoint = hitResult.Location;
	return result;
}

void ATankAIController_2::OnFire()
{
	if (this->actorCopy != NULL && this->GetWorldPoint()) {
		/*FActorSpawnParameters spawnParams;
		spawnParams.Template = this->actorCopy;
		spawnParams.Owner = this->GetOwner();

		AActor* myActor = this->GetWorld()->SpawnActor<AActor>(this->actorCopy->GetClass(), spawnParams);
		myActor->AttachToActor(this->GetOwner(), FAttachmentTransformRules::KeepRelativeTransform); //works but does not show hierarchy in outliner during gameplay.
		myActor->SetActorHiddenInGame(false);
		myActor->SetActorLocation(this->latestWorldPoint);
		myActor->SetActorRotation(this->actorCopy->GetActorRotation());*/

		UE_LOG(LogTemp, Display, TEXT("Firing on: %s"), *this->latestWorldPoint.ToString());
	}
}
