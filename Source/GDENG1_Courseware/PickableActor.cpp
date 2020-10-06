// Fill out your copyright notice in the Description page of Project Settings.


#include "PickableActor.h"
#include "CustomFPSCharacter.h"
#include "PlayerInventoryManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APickableActor::APickableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APickableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APickableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	APawn* playerPawn = UGameplayStatics::GetPlayerController(this->GetWorld(), 0)->GetPawn();	
	if (this->hasOverlap && this->destructibleOwner != nullptr && this->actorOverlap != nullptr && this->actorOverlap->GetName() == playerPawn->GetName())
	{
		APlayerInventoryManager::GetSharedInstance()->SetActiveIndex(this->itemIndex);
		this->Destroy();
		this->destructibleOwner->Destroy();
	}
}

void APickableActor::SetOverlap(AActor* overlappingActor, bool flag)
{
	this->actorOverlap = overlappingActor;
	this->hasOverlap = flag;
}

void APickableActor::SetActorParent(AActor* parent)
{
	this->destructibleOwner = parent;
}

void APickableActor::SetItemIndex(int index)
{
	this->itemIndex = index;
}

