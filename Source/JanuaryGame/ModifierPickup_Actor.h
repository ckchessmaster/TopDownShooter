// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ModifierPickup_Actor.generated.h"

UCLASS()
class JANUARYGAME_API AModifierPickup_Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AModifierPickup_Actor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* PickupArea;
};
