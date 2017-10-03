// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "JanuaryGameGameMode.generated.h"

/**
 * 
 */
UCLASS()
class JANUARYGAME_API AJanuaryGameGameMode : public AGameMode
{
	GENERATED_BODY()
	
	
public:

	// Animation callers for mods ---------------------------------------------------------------------------------
	UFUNCTION(BlueprintImplementableEvent, Category = Animation)
	void LightningModAnimation(AActor* HitActor, AActor* FirstHit, AActor* SecondHit);

	UFUNCTION(BlueprintImplementableEvent, Category = Animation)
	void ExplosionModAnimation(AActor* HitActor);
};
