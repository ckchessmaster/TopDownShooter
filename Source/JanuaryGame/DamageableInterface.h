// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DamageableInterface.generated.h"

// Interface for all damageable actors that gets needed basic info


UINTERFACE(MinimalAPI)
class UDamageableInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IDamageableInterface
{
	GENERATED_IINTERFACE_BODY()

	virtual int32 GetTeam();
	virtual float GetCurrentHP();
	virtual float GetMaxHP();

	virtual void SetCurrentHP(float Amount);
};
