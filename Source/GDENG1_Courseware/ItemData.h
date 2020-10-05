// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class GDENG1_COURSEWARE_API ItemData
{
public:
	ItemData(FName name, float bulletSize, float bulletSpeed);
	~ItemData();

	FName GetItemName() const;
	FString GetItemNameString() const;
	float GetBulletSize() const;
	float GetBulletSpeed() const;

private:
	FName itemName; //use FName since it's case insensitive;
	float bulletSizeModifier = 1.0f;
	float bulletSpeedModifier = 1.0f;
};
