// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GameFramework/DamageType.h"
#include "GravityMarker_Actor.h"

#include "WeaponModifiers.generated.h"

UENUM(BlueprintType)
enum class EModifierType : uint8
{
	ENone			UMETA(DisplayName = "None"),
	EFire			UMETA(DisplayName = "Fire"),
	EIce			UMETA(DisplayName = "Ice"),
	ELightning		UMETA(DisplayName = "Lightning"),
	EExplosive		UMETA(DisplayName = "Explosive"),
	ECrit			UMETA(DisplayName = "CriticalStrike")
};

UENUM(BlueprintType)
enum class ESecretModifierType : uint8
{
	ENone			UMETA(DisplayName = "None"),
	ESplit			UMETA(DisplayName = "SplitShot"),
	EGravity		UMETA(DisplayName = "Gravitation"),
	EChaos			UMETA(DisplayName = "Chaos"),
	EVampire		UMETA(DisplayName = "Lifesteal"),
	EDark			UMETA(DisplayName = "Dark Pact")
};

USTRUCT(BlueprintType)
struct FDamageEventExtended : public FDamageEvent
{
	GENERATED_USTRUCT_BODY()

	// Array of all active normal mods
	UPROPERTY(BlueprintReadOnly, Category = Config)
	TArray<EModifierType> ActiveNormalMods;

	// Array of all active secret mods
	UPROPERTY(BlueprintReadOnly, Category = Config)
	TArray<ESecretModifierType> ActiveSecretMods;
};

UCLASS()
class JANUARYGAME_API UWeaponModifiers : public UObject
{
	GENERATED_BODY()

public:
	
	UWeaponModifiers();

	// Add a DoT that does 50 damage a second
	static void FireMod(AActor* Enemy);
	// Slow enemy move/attack speed by 30%
	static void IceMod(AActor* Enemy);
	// Send lighting (which applies other mods) to up to two other enemies
	static void LightningMod(AActor* Enemy, AActor* Projectile, FDamageEventExtended ActiveMods);
	// AoE explosion on impact with enemy that does more damage the closer an enemy is to it
	static void ExplosiveMod(AActor* Enemy, AActor* Projectile, FDamageEventExtended ActiveMods);
	// 25% chance to get a 2.5x crit
	static float CritMod(AActor* Projectile);

	// Create two more identical projectiles
	static void SplitMod(AActor* Projectile);
	// Leaves a marker behind that activates when enough are close enough does massive AoE damage
	static void GravityMod(AActor* Enemy, FDamageEventExtended ActiveMods);
	// Randomly applies another mod
	static float ChaosMod(AActor* Enemy, AActor* Projectile, FDamageEventExtended ActiveMods);
	// Return 50% of damage as health
	static void VampireMod(AActor* Projectile);
	// Do 2% more damage for each 1% of HP missing
	static float DarkMod(AActor* Projectile);
};