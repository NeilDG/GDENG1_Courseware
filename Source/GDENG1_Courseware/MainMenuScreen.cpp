// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuScreen.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UMainMenuScreen::UMainMenuScreen()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMainMenuScreen::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMainMenuScreen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMainMenuScreen::OnSnowmanClicked()
{
	UE_LOG(LogTemp, Display, TEXT("On snowman clicked!"));
	UGameplayStatics::OpenLevel(this, "SnowmanLevel", true);
}

void UMainMenuScreen::OnEscapeClicked()
{
	UE_LOG(LogTemp, Display, TEXT("On escape clicked!"));
	UGameplayStatics::OpenLevel(this, "EscapeLevel", true);
}

