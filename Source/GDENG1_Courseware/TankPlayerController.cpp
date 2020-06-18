// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	ATankPawn* myPawn = this->GetControlledTank();

	if (myPawn != NULL) {
		UE_LOG(LogTemp, Display, TEXT("Player controller possessing %s"), *myPawn->GetName());
	}
	
}
ATankPawn* ATankPlayerController::GetControlledTank() const
{
	return this->GetPawn<ATankPawn>();
}
