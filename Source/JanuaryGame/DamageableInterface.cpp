// Fill out your copyright notice in the Description page of Project Settings.

#include "JanuaryGame.h"
#include "DamageableInterface.h"


UDamageableInterface::UDamageableInterface(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

int32 IDamageableInterface::GetTeam() { return 0; }
float IDamageableInterface::GetCurrentHP() { return 0.0f; }
float IDamageableInterface::GetMaxHP() { return 0.0f; }

void IDamageableInterface::SetCurrentHP(float Amount) {}
