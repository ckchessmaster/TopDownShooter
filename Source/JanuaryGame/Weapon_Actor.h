// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile_Actor.h"

#include "WeaponModifiers.h"

#include "Weapon_Actor.generated.h"

UENUM(BlueprintType)
enum class EProjectileType : uint8
{
	EBullet			UMETA(DisplayName = "Bullet"),
	EArea			UMETA(DisplayName = "Area"),
	EBeam			UMETA(DisplayName = "Beam")
};

USTRUCT()
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

	// The attack speed of the weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	float TimeBetweenShots;

	// Which of the 3 modes are we in?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	EProjectileType ProjectileType;

	// Base damage for the weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	float Range;

	// Array of all active mods
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	FDamageEventExtended ActiveMods;
};

UCLASS()
class JANUARYGAME_API AWeapon_Actor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeapon_Actor();

	// Setup the timer for repeated firing
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void PrepareFire();

	// Fire the weapon (May later remove from blueprint)
	UFUNCTION(BlueprintNativeEvent, Category = Weapon)
	void Fire();
	void Fire_Implementation();

	// Stop firing the weapon
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void StopFiring();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	FWeaponData WeaponConfig;

	// Are we currently firing the weapon (false by default)
	bool HasStartedFiring = false;

	// Handle to identify the cooldown timer
	FTimerHandle WeaponTimer;	

	// The blueprint of the projectile
	TSubclassOf<class AProjectile_Actor> ProjectileBlueprint;
};
