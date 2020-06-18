// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "GameFramework/Actor.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	ATankPawn* myPawn = this->GetControlledTank();
	ATankPawn* myPlayer = this->GetPlayerTank();
	if (myPlayer != NULL && myPawn != NULL) {
		UE_LOG(LogTemp, Warning, TEXT("AI %s found player %s"), *myPawn->GetName(), *myPlayer->GetName());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Enemy tank or player tank is not assigned. Cancelling AI controller."));
	}
	
}

ATankPawn* ATankAIController::GetControlledTank() const
{
	return this->GetPawn<ATankPawn>();
}

ATankPawn* ATankAIController::GetPlayerTank() const
{
	ATankPawn* playerPawn = this->GetWorld()->GetFirstPlayerController()->GetPawn<ATankPawn>();
	return playerPawn;
}
