// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
//#include "WeaponModifiers.h"

#include "GravityMarker_Actor.generated.h"

UCLASS()
class JANUARYGAME_API AGravityMarker_Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGravityMarker_Actor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	int32 Team;

	//TArray<EModifierType> ActiveNormalMods;
	//TArray<ESecretModifierType> ActiveSecretMods;
};
