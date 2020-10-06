// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableItem.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UPickableItem::UPickableItem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPickableItem::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPickableItem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	APawn* playerPawn = UGameplayStatics::GetPlayerController(this->GetWorld(), 0)->GetPawn();
	if(this->hasOverlap && this->actorOverlap->GetName() == playerPawn->GetName())
	{
		UE_LOG(LogTemp, Log, TEXT("I am picking up item: %s"), *this->GetOwner()->GetName());
		this->GetOwner()->Destroy();
		this->destructibleOwner->Destroy();
	}
}

void UPickableItem::SetActorParent(AActor* parent)
{
	this->destructibleOwner = parent;
}

void UPickableItem::SetOverlap(AActor* overlappingActor, bool flag)
{
	this->actorOverlap = overlappingActor;
	this->hasOverlap = flag;

	if(this->hasOverlap)
	{
		UE_LOG(LogTemp, Log, TEXT("Overlap detected with: %s"), *this->actorOverlap->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Overlap exitted: %s"), *this->actorOverlap->GetName());
	}
	
}

