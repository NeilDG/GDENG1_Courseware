// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn_2.h"

// Sets default values
ATankPawn_2::ATankPawn_2()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATankPawn_2::Move(float throttleSpeed)
{
	float speed = this->tankBody->GetMass() * this->TRACK_STRENGTH;
	FVector forceVector = this->GetActorForwardVector() * throttleSpeed * speed;
	FVector lTrackLoc = this->leftTrack->GetComponentLocation();
	FVector rTrackLoc = this->rightTrack->GetComponentLocation();

	this->tankBody->AddForceAtLocation(forceVector, lTrackLoc);
	this->tankBody->AddForceAtLocation(forceVector, rTrackLoc);
	UE_LOG(LogTemp, Display, TEXT("Attempting to move with vector %s, Speed of %f"), *forceVector.ToString(), (throttleSpeed * speed));
}

void ATankPawn_2::Sideways(float throttleSpeed)
{
}

// Called when the game starts or when spawned
void ATankPawn_2::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATankPawn_2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATankPawn_2::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

