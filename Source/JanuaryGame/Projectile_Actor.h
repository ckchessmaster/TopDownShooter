// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "WeaponModifiers.h"

#include "Projectile_Actor.generated.h"



UCLASS()
class JANUARYGAME_API AProjectile_Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile_Actor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when this actor bumps into a blocking object
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpluse, const FHitResult &Hit) override;

	// Give blueprint a copy of the active mods struct
	UFUNCTION(BlueprintCallable, Category = Config)
	FDamageEventExtended BPGetActiveMods();

	float Damage;

	// Bool to make sure we don't infinitely split
	bool HasSplit;

	// Array of all active mods
	FDamageEventExtended ActiveMods;
};
