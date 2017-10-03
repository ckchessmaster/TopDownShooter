// Fill out your copyright notice in the Description page of Project Settings.

#include "JanuaryGame.h"
#include "Projectile_Actor.h"


// Sets default values
AProjectile_Actor::AProjectile_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AProjectile_Actor::BeginPlay()
{
	Super::BeginPlay();
	
	if (ActiveMods.ActiveSecretMods.Contains(ESecretModifierType::ESplit) && !HasSplit)
	{
		UWeaponModifiers::SplitMod(this);
	}
}

void AProjectile_Actor::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpluse, const FHitResult &Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpluse, Hit);

	if (Other && Other->bCanBeDamaged)
	{
		// Make sure damage instigator is still alive (may need to check later)
		ACharacter* character = Cast<ACharacter>(GetOwner()->GetOwner());
		if (character)
		{
			Other->TakeDamage(Damage, ActiveMods, character->GetController(), this);
		}
	}
	else if (ActiveMods.ActiveNormalMods.Contains(EModifierType::EExplosive))
	{
		UWeaponModifiers::ExplosiveMod(nullptr, this, ActiveMods);
	}

	Destroy();
}

FDamageEventExtended AProjectile_Actor::BPGetActiveMods()
{
	return ActiveMods;
}