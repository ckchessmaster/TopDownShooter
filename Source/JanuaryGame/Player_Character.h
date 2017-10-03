// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Weapon_Actor.h"
#include "WeaponModifiers.h"
#include "DamageableInterface.h"

#include "Player_Character.generated.h"

UCLASS()
class JANUARYGAME_API APlayer_Character : public ACharacter, public IDamageableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayer_Character();

	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	// Start Damageable Interface
	virtual int32 GetTeam() override;
	virtual float GetCurrentHP() override;
	virtual float GetMaxHP() override;
	virtual void SetCurrentHP(float Amount) override;
	// End Damageable Interface

	// Load the character state
	UFUNCTION()
	void LoadCharacter();

	// This should be set in the editor via a blueprint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	AWeapon_Actor* PlayerWeapon;

	// Current Health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
	float CurrentHP = 100;

	// Max Health
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
	float MaxHP = 100;

	UPROPERTY()
	int32 Team;

	// How much energy (currency) do we have?
	UPROPERTY(BlueprintReadOnly, Category = Player)
	float Energy = 0;

	// The number of overloads available
	UPROPERTY(BlueprintReadOnly, Category = Player)
	int32 NumOverloads;

	// Array of all modifiers we currently have
	UPROPERTY(BlueprintReadOnly)
	TArray<EModifierType> OwnedMods;

	// Array of all secret modifiers we currently have
	UPROPERTY(BlueprintReadOnly)
	TArray<ESecretModifierType> OwnedSecretMods;
};
