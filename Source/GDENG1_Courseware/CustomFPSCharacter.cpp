// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomFPSCharacter.h"
#include "Animation/AnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

ACustomFPSCharacter::ACustomFPSCharacter(): AFP_FirstPersonCharacter(){

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

		UPrimitiveComponent* myActorComponent = (UPrimitiveComponent*)myActor->GetRootComponent();
		myActorComponent->AddImpulseAtLocation(ShootDir * this->WeaponDamage, this->projectileSpawnPos);
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("No projectile copy detected."));
	}
	
}
