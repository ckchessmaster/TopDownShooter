// Fill out your copyright notice in the Description page of Project Settings.

#include "JanuaryGame.h"
#include "Weapon_Actor.h"
#include "Globals.h"


// Sets default values
AWeapon_Actor::AWeapon_Actor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FString finalPath = UGlobals::RootPath + FString("Class'/Game/Main/Projectile_BPActor.Projectile_BPActor_C'");
	static ConstructorHelpers::FObjectFinder<UClass>Blueprint(*finalPath);
	if (Blueprint.Object)
	{
		ProjectileBlueprint = (UClass*)Blueprint.Object;
	}

	if (!WeaponConfig.ActiveMods.ActiveNormalMods.Contains(EModifierType::ENone))
	{
		WeaponConfig.ActiveMods.ActiveNormalMods.Add(EModifierType::ENone);
	}
	if (!WeaponConfig.ActiveMods.ActiveSecretMods.Contains(ESecretModifierType::ENone))
	{
		WeaponConfig.ActiveMods.ActiveSecretMods.Add(ESecretModifierType::ENone);
	}	
}

void AWeapon_Actor::PrepareFire()
{
	//Make sure we aren't already firing then start firing
	if (!HasStartedFiring)
	{
		HasStartedFiring = true;

		GetWorldTimerManager().SetTimer(WeaponTimer, this, &AWeapon_Actor::Fire, WeaponConfig.TimeBetweenShots, true, 0);
	}
	else
	{
		if (WeaponTimer.IsValid()) 
		{
			GetWorldTimerManager().UnPauseTimer(WeaponTimer);
		}
	}
}

void AWeapon_Actor::Fire_Implementation()
{
	switch (WeaponConfig.ProjectileType)
	{
	default:
		break;
	case EProjectileType::EBullet:
	{
		// Spawn the projectile in front of the player
		FVector spawnLocation = (GetActorForwardVector() * 150) + GetActorLocation();

		// Deffer spawn so that we can add the modifiers before its spawned into the world
		FTransform dummyTransform;
		AProjectile_Actor* projectile = GetWorld()->SpawnActorDeferred<AProjectile_Actor>(ProjectileBlueprint, dummyTransform, this, nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
		
		// Add the active mods to the projectile
		if (projectile)
		{
			projectile->ActiveMods = WeaponConfig.ActiveMods;
			projectile->Damage = WeaponConfig.Damage;

			// Finish spawning
			FTransform* transform = new FTransform(GetActorRotation(), spawnLocation, FVector(0, 0, 0));
			projectile->FinishSpawning(*transform, true, nullptr);
		}
	}
	case EProjectileType::EArea:
		// @ToDo later
		break;
	case EProjectileType::EBeam:
		break;
	}
}

void AWeapon_Actor::StopFiring()
{
	if(WeaponTimer.IsValid())
	{
		GetWorldTimerManager().PauseTimer(WeaponTimer);
	}
}