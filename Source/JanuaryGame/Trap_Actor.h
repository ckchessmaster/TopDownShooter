// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Trap_Actor.generated.h"

UCLASS()
class JANUARYGAME_API ATrap_Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrap_Actor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = Trigger)
	void InitializeTrap();
	
	UFUNCTION(BlueprintNativeEvent, Category = Trigger)
	void StartTrap();
	void StartTrap_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Trigger)
	void StopTrap();
	void StopTrap_Implementation();

	UFUNCTION()
	void OnDamageBoxBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnDamageBoxEndOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintNativeEvent, Category = Trigger)
	void DealDamage(float DeltaTime, AActor* Actor);
	virtual void DealDamage_Implementation(float DeltaTime, AActor* Actor);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	float InitialDelay = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	float TrapTime = 1.0f;

	// Should this trap always be active
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	bool AlwaysActive = false;

	// Is the trap currently firing
	UPROPERTY(BlueprintReadWrite)
	bool TrapActive = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	float BaseDamage;

	float TimeSinceLastDamage = 0.0f;
	FTimerHandle TrapTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* NavigationModifierBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* DamageBox;

};
