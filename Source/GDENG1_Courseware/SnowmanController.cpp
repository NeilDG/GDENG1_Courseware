// Fill out your copyright notice in the Description page of Project Settings.


#include "SnowmanController.h"

// Sets default values for this component's properties
USnowmanController::USnowmanController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USnowmanController::BeginPlay()
{
	Super::BeginPlay();

	//bind input component
	this->snowmanPawn->InputComponent->BindAxis(this->MOVE_X_KEY, this, &USnowmanController::MoveX);
	this->snowmanPawn->InputComponent->BindAxis(this->MOVE_Y_KEY, this, &USnowmanController::MoveY);
	UE_LOG(LogTemp, Display, TEXT("Binded actions"));
}


// Called every frame
void USnowmanController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (this->alongX) {
		FVector location = this->snowmanPawn->GetTransform().GetLocation();
		location.X += this->movementX * DeltaTime * this->SPEED_MULTIPLIER;
		this->snowmanPawn->SetActorLocation(location);
		//UE_LOG(LogTemp, Display, TEXT("Location X: %f"), location.X);
	}

	if (this->alongY) {
		FVector location = this->snowmanPawn->GetTransform().GetLocation();
		location.Y += this->movementY * DeltaTime * this->SPEED_MULTIPLIER;
		this->snowmanPawn->SetActorLocation(location);
		//UE_LOG(LogTemp, Display, TEXT("Location Y: %f"), location.Y);
	}
}

void USnowmanController::MoveX(float axisValue)
{
	//UE_LOG(LogTemp, Display, TEXT("Move X: %f"), axisValue);

	//to move to delta-time, use flags
	this->movementX = FMath::Clamp(axisValue, -1.0f, 1.0f);
	if (this->movementX != 0.0f) {
		this->alongX = true;
		this->alongY = false;
	}
	
}

void USnowmanController::MoveY(float axisValue)
{
	//UE_LOG(LogTemp, Display, TEXT("Move Y: %f"), axisValue);
	this->movementY = FMath::Clamp(axisValue, -1.0f, 1.0f);
	if (this->movementY != 0.0f) {
		this->alongY = true;
		this->alongX = false;
	}
}

