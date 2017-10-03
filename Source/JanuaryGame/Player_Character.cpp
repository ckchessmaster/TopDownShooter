// Fill out your copyright notice in the Description page of Project Settings.

#include "JanuaryGame.h"
#include "Player_Character.h"


// Sets default values
APlayer_Character::APlayer_Character()
{
	bCanBeDamaged = true;
}

void APlayer_Character::BeginPlay()
{
	Super::BeginPlay();

	LoadCharacter();
}

float APlayer_Character::TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	SetCurrentHP(-1 * DamageAmount);

	return DamageAmount;
}


// Start Damageable Interface
int32 APlayer_Character::GetTeam()
{
	return Team;
}

float APlayer_Character::GetCurrentHP()
{
	return CurrentHP;
}

float APlayer_Character::GetMaxHP()
{
	return MaxHP;
}

void APlayer_Character::SetCurrentHP(float Amount)
{
	CurrentHP = CurrentHP + Amount;

	if (CurrentHP > MaxHP)
	{
		CurrentHP = MaxHP;
	}
}
// End Damageable Interface

// @ToDo
void APlayer_Character::LoadCharacter()
{
	CurrentHP = 1000;
	MaxHP = 1000;
	Energy = 0;

	// Create and fill mod list remember that they need to be added in reverse order
	//PlayerWeapon->WeaponConfig.ActiveMods.ActiveSecretMods.Add(ESecretModifierType::EVampire);
	//PlayerWeapon->WeaponConfig.ActiveMods.ActiveNormalMods.Add(EModifierType::EExplosive);
	//PlayerWeapon->WeaponConfig.ActiveMods.ActiveNormalMods.Add(EModifierType::ELightning);
	
	

	PlayerWeapon->WeaponConfig.TimeBetweenShots = 0.2f;
	PlayerWeapon->WeaponConfig.ProjectileType = EProjectileType::EBullet;
	PlayerWeapon->WeaponConfig.Damage = 10.0f;
}
