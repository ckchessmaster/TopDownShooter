// Fill out your copyright notice in the Description page of Project Settings.

#include "JanuaryGame.h"
#include "Enemy_Character.h"
#include "WeaponModifiers.h"
#include "Player_Character.h"
#include "Trap_Actor.h"


// Sets default values
AEnemy_Character::AEnemy_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bCanBeDamaged = true;
}

// Called when the game starts or when spawned
void AEnemy_Character::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AEnemy_Character::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (CurrentHP <= 0)
	{
		// Cleanup weapon and timers before destroying ourselves
		GetWorldTimerManager().ClearAllTimersForObject(MyWeapon);
		MyWeapon->Destroy();

		Destroy();
	}
}

float AEnemy_Character::TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	float finalDamage = DamageAmount;

	FDamageEventExtended* customDamageEvent = (FDamageEventExtended*)(&DamageEvent);
	if (customDamageEvent)
	{
		for (int32 i = customDamageEvent->ActiveNormalMods.Num() - 1; i >= 0; i--)
		{
			switch (customDamageEvent->ActiveNormalMods[i])
			{
			default:
				break;
			case EModifierType::EFire:
				UWeaponModifiers::FireMod(this); break;
			case EModifierType::EIce:
				UWeaponModifiers::IceMod(this); break;
			case EModifierType::ELightning:
			{
				UWeaponModifiers::LightningMod(this, DamageCauser, *customDamageEvent);
				customDamageEvent->ActiveNormalMods.Remove(EModifierType::ELightning);
				break;
			}
			case EModifierType::EExplosive:
			{
				UWeaponModifiers::ExplosiveMod(this, DamageCauser, *customDamageEvent);
				customDamageEvent->ActiveNormalMods.Remove(EModifierType::EExplosive);
				break;
			}
			
			case EModifierType::ECrit:
				finalDamage = UWeaponModifiers::CritMod(DamageCauser); break;
			}
		}
		for (ESecretModifierType mod : customDamageEvent->ActiveSecretMods)
		{
			switch (mod)
			{
			default:
				break;
			case ESecretModifierType::ESplit:
				break; // Do nothing since this is taken care of by the projectile itself
			case ESecretModifierType::EGravity:
				UWeaponModifiers::GravityMod(this, *customDamageEvent); break;
			case ESecretModifierType::EChaos:
				finalDamage = UWeaponModifiers::ChaosMod(this, DamageCauser, *customDamageEvent); break;
			case ESecretModifierType::EVampire:
				UWeaponModifiers::VampireMod(DamageCauser); break;
			case ESecretModifierType::EDark:
				finalDamage = finalDamage + UWeaponModifiers::DarkMod(DamageCauser); break;
			}
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Warning damage event cast failure!!!!");
	}
	
	SetCurrentHP(-1 * finalDamage);

	// Rotate towards player if the damage came from the player (ie won't trigger if the damage came from aoe side explosion only direct damage from player)
	APlayer_Character* player = nullptr;
	ATrap_Actor* emergencyPatch = Cast<ATrap_Actor>(DamageCauser);
	if (!emergencyPatch)
	{
		player = Cast<APlayer_Character>(DamageCauser->GetOwner()->GetOwner());
	}

	if (player)
	{
		FRotator rotation = FRotationMatrix::MakeFromX(player->GetActorLocation() - GetActorLocation()).Rotator();
		SetActorRelativeRotation(rotation, true);
	}

	return finalDamage;
}

// Start Damageable Interface
int32 AEnemy_Character::GetTeam()
{
	return Team;
}

float AEnemy_Character::GetCurrentHP()
{
	return CurrentHP;
}

float AEnemy_Character::GetMaxHP()
{
	return MaxHP;
}

void AEnemy_Character::SetCurrentHP(float Amount)
{
	CurrentHP = CurrentHP + Amount;

	if (CurrentHP > MaxHP)
	{
		CurrentHP = MaxHP;
	}
}
// End Damageable Interface