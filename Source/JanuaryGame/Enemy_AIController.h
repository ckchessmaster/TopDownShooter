// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
//

#include "Enemy_AIController.generated.h"

UCLASS()
class JANUARYGAME_API AEnemy_AIController : public AAIController
{
	GENERATED_BODY()

	UFUNCTION()
	void SenseStuff(TArray<AActor*> Actors);
	
	// May remove later
	FVector EnemyLocation;
	
public:
	AEnemy_AIController();

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly)
	AActor* Enemy;
};
