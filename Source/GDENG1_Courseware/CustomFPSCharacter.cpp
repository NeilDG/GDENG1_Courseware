// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomFPSCharacter.h"
#include "Animation/AnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "PlayerInventoryManager.h"

ACustomFPSCharacter::ACustomFPSCharacter(): AFP_FirstPersonCharacter(){

}

void ACustomFPSCharacter::BeginPlay()
{
	AFP_FirstPersonCharacter::BeginPlay();
	this->activeItem = APlayerInventoryManager::GetSharedInstance()->GetBulletData(APlayerInventoryManager::BASIC_BULLET_INDEX);
}

void ACustomFPSCharacter::OnFire() {
	AFP_FirstPersonCharacter::OnFire();

	if (this->projectileCopy != NULL) {
		//spawn additional projectile
		FActorSpawnParameters spawnParams;
		spawnParams.Template = this->projectileCopy;
		spawnParams.Owner = this->GetOwner();

		// Code taken from FPS character
		FVector ShootDir = FVector::ZeroVector;
		FVector StartTrace = FVector::ZeroVector;
		FRotator CamRot;
		APlayerController* playerController = this->GetController <APlayerController>();
		playerController->GetPlayerViewPoint(StartTrace, CamRot);
		ShootDir = CamRot.Vector();

		FVector spawnLocation = this->projectileSpawnPos;
		FRotator spawnRotation = this->GetActorRotation();

		AActor* myActor = this->GetWorld()->SpawnActor<AActor>(this->projectileCopy->GetClass(), spawnParams);
		myActor->AttachToActor(this->GetOwner(), FAttachmentTransformRules::KeepRelativeTransform); //works but does not show hierarchy in outliner during gameplay.
		myActor->SetActorHiddenInGame(false);
		myActor->SetActorLocation(spawnLocation);
		myActor->SetActorRotation(spawnRotation);
		myActor->SetActorScale3D(FVector(this->activeItem->GetBulletSize()));
		
		UPrimitiveComponent* myActorComponent = (UPrimitiveComponent*)myActor->GetRootComponent();
		myActorComponent->AddImpulseAtLocation(ShootDir * this->WeaponDamage * this->activeItem->GetBulletSpeed(), this->projectileSpawnPos);

		UE_LOG(LogTemp, Log, TEXT("Current item equipped: %s Speed: %f Size: %f"), *this->activeItem->GetItemName().ToString(), this->activeItem->GetBulletSpeed(), this->activeItem->GetBulletSize());
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("No projectile copy detected."));
	}
	
}
