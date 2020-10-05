// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemData.h"

ItemData::ItemData(FName name, float bulletSize, float bulletSpeed)
{
	this->itemName = name;
	this->bulletSizeModifier = bulletSize;
	this->bulletSpeedModifier = bulletSpeed;
}

FName ItemData::GetItemName() const
{
	return this->itemName;
}

FString ItemData::GetItemNameString() const
{
	return this->itemName.ToString();
}

float ItemData::GetBulletSize() const
{
	return this->bulletSizeModifier;
}

float ItemData::GetBulletSpeed() const
{
	return this->bulletSpeedModifier;
}

ItemData::~ItemData()
{
	
}
