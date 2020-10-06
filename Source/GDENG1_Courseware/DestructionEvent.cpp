// Fill out your copyright notice in the Description page of Project Settings.


#include "DestructionEvent.h"
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
	UE_LOG(LogTemp, Warning, TEXT("I am destroying!!"));
	
	//spawn additional projectile
	UItemLibrary* itemLibrary = static_cast<UItemLibrary*>(this->itemLibraryActor->GetComponentByClass(UItemLibrary::StaticClass()));
	AActor* itemCopy = itemLibrary->GetRandomItem();
	FActorSpawnParameters spawnParams;
	spawnParams.Template = itemCopy;
	spawnParams.Owner = this->GetOwner();

	FVector spawnLocation = this->GetOwner()->GetActorLocation();
	FRotator spawnRotation = this->GetOwner()->GetActorRotation();

	AActor* myActor = this->GetWorld()->SpawnActor<AActor>(itemCopy->GetClass(), spawnParams);
	//myActor->AttachToActor(this->GetOwner(), FAttachmentTransformRules::KeepRelativeTransform); //works but does not show hierarchy in outliner during gameplay.
	UDestructionEvent::SetEnabled(myActor, true);
	myActor->SetActorLocation(spawnLocation);
	myActor->SetActorRotation(spawnRotation);
	myActor->FindComponentByClass<UPickableItem>()->SetActorParent(this->GetOwner());
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

