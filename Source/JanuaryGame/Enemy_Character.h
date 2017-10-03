// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Weapon_Actor.h"
#include "DamageableInterface.h"

#include "Enemy_Character.generated.h"

UCLASS()
class JANUARYGAME_API AEnemy_Character : public ACharacter, public IDamageableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy_Character();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	// Start Damageable Interface
	virtual int32 GetTeam() override;
	virtual float GetCurrentHP() override;
	virtual float GetMaxHP() override;
	virtual void SetCurrentHP(float Amount) override;
	// End Damageable Interface

	// This should be set in the editor via a blueprint
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	AWeapon_Actor* MyWeapon;

	// Current Health
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player)
	float CurrentHP = 100;

	// Max Health
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Player)
	float MaxHP = 100;

	UPROPERTY()
	int32 Team;
};
