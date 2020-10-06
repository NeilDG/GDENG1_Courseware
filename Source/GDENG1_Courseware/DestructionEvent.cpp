// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructionEvent.h"
#include "PickableActor.h"
#include "PickableItem.h"

// Sets default values for this component's properties
UDestructionEvent::UDestructionEvent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	this->triggered = false;
}


// Called when the game starts
void UDestructionEvent::BeginPlay()
{
	Super::BeginPlay();

	/*if(this->itemCopy != NULL)
	{
		UDestructionEvent::SetEnabled(this->itemCopy, false);
	}*/
}


// Called every frame
void UDestructionEvent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDestructionEvent::OnFracture(const FVector& HitPoint, const FVector& HitDirection)
{
	
	if(this->triggered)
	{
		return;
	}

	this->triggered = true;
	//spawn additional projectile
	UItemLibrary* itemLibrary = static_cast<UItemLibrary*>(this->itemLibraryActor->GetComponentByClass(UItemLibrary::StaticClass()));
	AActor* itemCopy = itemLibrary->GetRandomItem();
	UE_LOG(LogTemp, Warning, TEXT("Dropped item: %s"), *itemCopy->GetName());
	
	FActorSpawnParameters spawnParams;
	spawnParams.Template = itemCopy;
	spawnParams.Owner = this->GetOwner();

	const FVector spawnLocation = this->GetOwner()->GetActorLocation();
	const FRotator spawnRotation = this->GetOwner()->GetActorRotation();

	APickableActor* myActor = this->GetWorld()->SpawnActor<APickableActor>(itemCopy->GetClass(), spawnParams);
	myActor->AttachToActor(this->GetOwner(), FAttachmentTransformRules::KeepWorldTransform);
	UDestructionEvent::SetEnabled(myActor, true);
	myActor->SetActorLocation(spawnLocation);
	myActor->SetActorRotation(spawnRotation);
	myActor->SetActorParent(this->GetOwner());
	myActor->SetItemIndex(itemLibrary->GetRandomItemIndex());
	myActor->OnItemSetup();
}

void UDestructionEvent::SetEnabled(AActor* actor, bool flag)
{
	actor->SetActorHiddenInGame(!flag);
	
	TArray<AActor*> childActors;
	actor->GetAllChildActors(childActors);

	for (int i = 0; i < childActors.Num(); i++)
	{
		childActors[i]->SetActorHiddenInGame(!flag);
	}
}

