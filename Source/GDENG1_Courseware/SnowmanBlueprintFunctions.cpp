// Fill out your copyright notice in the Description page of Project Settings.


#include "SnowmanBlueprintFunctions.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
USnowmanBlueprintFunctions::USnowmanBlueprintFunctions()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USnowmanBlueprintFunctions::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USnowmanBlueprintFunctions::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USnowmanBlueprintFunctions::Move(bool alongX, bool alongY, float movementX, float movementY, float deltaTime)
{
	if (alongX) {
		FVector location = this->GetOwner()->GetActorLocation();
		location.X += movementX * deltaTime * this->SPEED_MULTIPLIER;
		this->GetOwner()->SetActorLocation(location);
		//UE_LOG(LogTemp, Display, TEXT("Location X: %f"), location.X);
	}

	if (alongY) {
		FVector location = this->GetOwner()->GetActorLocation();
		location.Y += movementY * deltaTime * this->SPEED_MULTIPLIER;
		this->GetOwner()->SetActorLocation(location);
		//UE_LOG(LogTemp, Display, TEXT("Location Y: %f"), location.Y);
	}
}

