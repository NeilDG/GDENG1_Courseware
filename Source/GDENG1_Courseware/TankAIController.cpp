// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	ATankPawn* myPawn = this->GetControlledTank();

	if (myPawn != NULL) {
		UE_LOG(LogTemp, Display, TEXT("AI controller possessing %s"), *myPawn->GetName());
	}
}

ATankPawn* ATankAIController::GetControlledTank() const
{
	return this->GetPawn<ATankPawn>();
}
