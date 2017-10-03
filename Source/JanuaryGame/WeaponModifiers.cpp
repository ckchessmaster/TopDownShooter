// Fill out your copyright notice in the Description page of Project Settings.

#include "JanuaryGame.h"
#include "WeaponModifiers.h"
#include "Globals.h"

#include "Projectile_Actor.h"
#include "Weapon_Actor.h"
#include "Player_Character.h"
#include "Enemy_Character.h"
#include "JanuaryGameGameMode.h"


UWeaponModifiers::UWeaponModifiers()
{
	// Blueprint'/Game/Main/GravityMarker_BPActor.GravityMarker_BPActor'
}

void UWeaponModifiers::FireMod(AActor* Enemy)
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, "I'M ON FIRE!!!!!");
}

void UWeaponModifiers::IceMod(AActor* Enemy)
{
	AEnemy_Character* enemyConverted = Cast<AEnemy_Character>(Enemy);

	//enemyConverted->MyWeapon->WeaponConfig.TimeBetweenShots = enemyConverted->GetCharacterMovement()->MaxWalkSpeed - (enemyConverted->MyWeapon->WeaponConfig.TimeBetweenShots * 0.3f);
	enemyConverted->GetCharacterMovement()->MaxWalkSpeed = enemyConverted->GetCharacterMovement()->MaxWalkSpeed - (enemyConverted->GetCharacterMovement()->MaxWalkSpeed * 0.3f);
}

void UWeaponModifiers::LightningMod(AActor* Enemy, AActor* Projectile, FDamageEventExtended ActiveMods)
{
	if (!Enemy) { return; }

	// For animation only
	AActor* secondHitActor = nullptr;

	TArray<FHitResult> outHits;
	TArray<AActor*> actorsToIgnore;
	actorsToIgnore.Add(Projectile->GetOwner()->GetOwner());
	actorsToIgnore.Add(Enemy);

	UGlobals::SphereTraceMulti(outHits, actorsToIgnore, Enemy->GetActorLocation(), Enemy->GetActorLocation(), Enemy->GetWorld(), 500.0f, false);

	AActor* newTarget = nullptr;
	for (FHitResult hit : outHits)
	{
		AActor* hitActor = hit.Actor.Get();
		IDamageableInterface* damageableActor = Cast<IDamageableInterface>(hitActor);
		if (damageableActor)
		{
			if (newTarget)
			{
				if (FVector::Dist(Projectile->GetActorLocation(), hitActor->GetActorLocation()) < FVector::Dist(Projectile->GetActorLocation(), newTarget->GetActorLocation()))
				{
					newTarget = hitActor;
				}
			}
			else
			{
				newTarget = hitActor;
			}
		}
	}
	AProjectile_Actor* convertedProjectile = Cast<AProjectile_Actor>(Projectile);

	// Remove the lightning modifier
	FDamageEventExtended damageModifiers = ActiveMods;
	damageModifiers.ActiveNormalMods.Remove(EModifierType::ELightning);

	if (newTarget)
	{
		// Testing ------------------------------------------------------------------
		UE_LOG(LogTemp, Warning, TEXT("These are the currently active mods: "));
		for (EModifierType mod : damageModifiers.ActiveNormalMods)
		{
			switch (mod)
			{
			default:
				UE_LOG(LogTemp, Warning, TEXT("NONE")); break;
			case EModifierType::EFire:
				UE_LOG(LogTemp, Warning, TEXT("Fire")); break;
			case EModifierType::EIce:
				UE_LOG(LogTemp, Warning, TEXT("Ice")); break;
			case EModifierType::ELightning:
				UE_LOG(LogTemp, Warning, TEXT("Lightning")); break;
			case EModifierType::EExplosive:
				UE_LOG(LogTemp, Warning, TEXT("Explosive")); break;
			case EModifierType::ECrit:
				UE_LOG(LogTemp, Warning, TEXT("Crit")); break;
			}
		}
		// ------- ------------------------------------------------------------------

		newTarget->TakeDamage(convertedProjectile->Damage, damageModifiers, nullptr, Projectile);

		// Now find the second target ignoring the last actor we just found also make this our 2nd arg for the animation
		actorsToIgnore.Add(newTarget);
		secondHitActor = newTarget;

		outHits.Empty();
		UGlobals::SphereTraceMulti(outHits, actorsToIgnore, newTarget->GetActorLocation(), newTarget->GetActorLocation(), newTarget->GetWorld(), 500.0f, false);
		newTarget = nullptr;
		for (FHitResult hit : outHits)
		{
			AActor* hitActor = hit.Actor.Get();
			IDamageableInterface* damageableActor = Cast<IDamageableInterface>(hitActor);
			if (damageableActor)
			{
				if (newTarget)
				{
					if (FVector::Dist(Projectile->GetActorLocation(), hitActor->GetActorLocation()) < FVector::Dist(Projectile->GetActorLocation(), newTarget->GetActorLocation()))
					{
						newTarget = hitActor;
					}
				}
				else
				{
					newTarget = hitActor;
				}
			}
		}
		if (newTarget)
		{
			newTarget->TakeDamage(convertedProjectile->Damage, damageModifiers, nullptr, Projectile);
		}
	}

	Cast<AJanuaryGameGameMode>(Enemy->GetWorld()->GetAuthGameMode())->LightningModAnimation(Enemy, secondHitActor, newTarget);
}

void UWeaponModifiers::ExplosiveMod(AActor* Enemy, AActor* Projectile, FDamageEventExtended ActiveMods)
{

		AProjectile_Actor* convertedProjectile = Cast<AProjectile_Actor>(Projectile);

		TArray<FHitResult> outHits;
		TArray<AActor*> actorsToIgnore;
		// Ignore self
		actorsToIgnore.Add(Projectile->GetOwner()->GetOwner());
		if (Enemy)
		{
			actorsToIgnore.Add(Enemy);
		}

		UGlobals::SphereTraceMulti(outHits, actorsToIgnore, Projectile->GetActorLocation(), Projectile->GetActorLocation(), Projectile->GetWorld(), 250.0f, false);

		for (FHitResult hit : outHits)
		{
			AActor* hitActor = hit.Actor.Get();
			IDamageableInterface* damageableActor = Cast<IDamageableInterface>(hitActor);
			if (damageableActor)
			{
				// Remove the explosive modifier (there will be no infinite explosions here)
				FDamageEventExtended damageModifiers = ActiveMods;
				damageModifiers.ActiveNormalMods.Remove(EModifierType::EExplosive);

				hitActor->TakeDamage(convertedProjectile->Damage, damageModifiers, nullptr, Projectile);
			}
		}
		Cast<AJanuaryGameGameMode>(Projectile->GetWorld()->GetAuthGameMode())->ExplosionModAnimation(Projectile);
}

float UWeaponModifiers::CritMod(AActor* Projectile)
{
	AProjectile_Actor* projectileConverted = Cast<AProjectile_Actor>(Projectile);
	float damage = projectileConverted->Damage;

	int32 chance = FMath::RandRange(1, 4);
	if (chance == 4)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, "CRIT!!");
		return damage * 2.5;
	}
	
	return damage;
}

void UWeaponModifiers::SplitMod(AActor* Projectile)
{	
	FTransform transform;
	AProjectile_Actor* leftProjectile = Cast<AProjectile_Actor>(Projectile->GetWorld()->SpawnActorDeferred<AActor>(Projectile->GetClass(), transform, Projectile->GetOwner(), nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn));
	AProjectile_Actor* rightProjectile = Cast<AProjectile_Actor>(Projectile->GetWorld()->SpawnActorDeferred<AActor>(Projectile->GetClass(), transform, Projectile->GetOwner(), nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn));

	AWeapon_Actor* projectileOwner = Cast<AWeapon_Actor>(Projectile->GetOwner());

	// Add the active mods to the projectile
	if (leftProjectile && rightProjectile && projectileOwner)
	{
		leftProjectile->ActiveMods = projectileOwner->WeaponConfig.ActiveMods;
		rightProjectile->ActiveMods = projectileOwner->WeaponConfig.ActiveMods;

		// Now set HasSplit to true so we don't infinitely split
		leftProjectile->HasSplit = true;
		rightProjectile->HasSplit = true;

		// Finish spawning
		FTransform* transformLeft = new FTransform(Projectile->GetActorRotation(), Projectile->GetActorLocation() + FVector(0, 100, 0), FVector(0, 0, 0));
		FTransform* transformRight = new FTransform(Projectile->GetActorRotation(), Projectile->GetActorLocation() - FVector(0, 100, 0), FVector(0, 0, 0));
		leftProjectile->FinishSpawning(*transformLeft, true, nullptr);
		rightProjectile->FinishSpawning(*transformRight, true, nullptr);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Warning something went wrong!!!");
	}

}

void UWeaponModifiers::GravityMod(AActor* Enemy, FDamageEventExtended ActiveMods)
{
	// Spawn markers at enemy location and set team
	IDamageableInterface* damageableEnemy = Cast<IDamageableInterface>(Enemy);
	if (damageableEnemy)
	{
		FTransform transform;

		FName path = FName(TEXT("Blueprint'/Game/Main/GravityMarker_BPActor.GravityMarker_BPActor'"));
		//TSubclassOf<class AGravityMarker_Actor> markerClass = (UClass*)UGlobals::LoadObjFromPath<AGravityMarker_Actor>(path);		

		//TSubclassOf<class AGravityMarker_Actor> markerClass = (UClass*)StaticLoadClass(UBlueprint::StaticClass(), NULL, *path.ToString());
		//UBlueprint test;// = (UBlueprint*)StaticLoadObject(UBlueprint::StaticClass(), NULL, *path.ToString());
		//TSubclassOf<class AGravityMarker_Actor> markerClass = (UClass*)
		//TSubclassOf<class AGravityMarker_Actor> markerClass = (UClass*)StaticLoadObject(UBlueprint::StaticClass(), NULL, *path.ToString());

		//FStringAssetReference asset(path.ToString());
		//UObject* test = asset.ResolveObject();
		//UBlueprint* markerClass = Cast<UBlueprint>(test);

		UBlueprint* markerClass = UGlobals::LoadBlueprintFromPath(path);

		if (markerClass)
		{
			AGravityMarker_Actor* marker = Enemy->GetWorld()->SpawnActorDeferred<AGravityMarker_Actor>(markerClass->GeneratedClass, transform, Enemy, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
			// @ToDo add mods
			marker->Team = damageableEnemy->GetTeam();
			FTransform* newTransform = new FTransform(Enemy->GetActorRotation(), Enemy->GetActorLocation());
			marker->FinishSpawning(*newTransform, true, nullptr);
			marker->AttachRootComponentToActor(Enemy, FName(TEXT("Head")), EAttachLocation::SnapToTarget, false);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, "NULL WARNING");
		}
	}
}

float UWeaponModifiers::ChaosMod(AActor* Enemy, AActor* Projectile, FDamageEventExtended ActiveMods)
{
	int32 selection = FMath::RandRange(1, 9);
	float finalDamage = Cast<AProjectile_Actor>(Projectile)->Damage;

	switch (selection)
	{
	default:
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		finalDamage = CritMod(Projectile); break;
	case 6:
		SplitMod(Projectile); break;
	case 7:
		GravityMod(Enemy, ActiveMods); break;
	case 8:
		VampireMod(Projectile); break;
	case 9:
		finalDamage = finalDamage + DarkMod(Projectile); break;
	}

	return finalDamage;
}

void UWeaponModifiers::VampireMod(AActor* Projectile)
{
	AProjectile_Actor* projectileConverted = Cast<AProjectile_Actor>(Projectile);
	IDamageableInterface* self = Cast<IDamageableInterface>(projectileConverted->GetOwner()->GetOwner());

	self->SetCurrentHP(projectileConverted->Damage);
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, "Healing!");
}

float UWeaponModifiers::DarkMod(AActor* Projectile)
{
	AProjectile_Actor* projectileConverted = Cast<AProjectile_Actor>(Projectile);
	IDamageableInterface* self = Cast<IDamageableInterface>(projectileConverted->GetOwner()->GetOwner());

	if (self)
	{
		float damageIncrease = self->GetMaxHP() - self->GetCurrentHP();

		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, "Power! Unlimited power: " + FString::SanitizeFloat(damageIncrease));

		return projectileConverted->Damage + damageIncrease;
	}

	return 0.0f;
}