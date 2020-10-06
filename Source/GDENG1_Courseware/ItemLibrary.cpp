// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemLibrary.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UItemLibrary::UItemLibrary()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UItemLibrary::BeginPlay()
{
	Super::BeginPlay();

	// ...
	//hide templates
	for(int i = 0; i < this->availableItems.Num(); i++)
	{
		this->availableItems[i]->SetActorHiddenInGame(true);
	}
}


// Called every frame
void UItemLibrary::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

AActor* UItemLibrary::GetRandomItem()
{
	const int index = FMath::RandRange(0, this->availableItems.Num() - 1);
	return this->availableItems[index];
}

int UItemLibrary::GetRandomItemIndex()
{
	const int index = FMath::RandRange(0, this->availableItems.Num() - 1);
	return index;
}

