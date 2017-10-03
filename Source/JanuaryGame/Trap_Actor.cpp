// Fill out your copyright notice in the Description page of Project Settings.

#include "JanuaryGame.h"
#include "Trap_Actor.h"
#include "WeaponModifiers.h"


// Sets default values
ATrap_Actor::ATrap_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup the NavigationBox box
	NavigationModifierBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Navigation"));
	NavigationModifierBox->SetBoxExtent(FVector(100, 100, 100), true);
	RootComponent = NavigationModifierBox;

	// Setup the damage box
	DamageBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Damage Box"));
	DamageBox->SetBoxExtent(FVector(150, 150, 150), true);

	DamageBox->bGenerateOverlapEvents = true;
	//DamageBox->OnComponentBeginOverlap.AddDynamic(this, &ATrap_Actor::OnDamageBoxBeginOverlap);
	//DamageBox->OnComponentEndOverlap.AddDynamic(this, &ATrap_Actor::OnDamageBoxEndOverlap);
}

// Called when the game starts or when spawned
void ATrap_Actor::BeginPlay()
{
	Super::BeginPlay();

	DamageBox->AttachTo(NavigationModifierBox);

}

// Called every frame
void ATrap_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Deal damage if someone is in the trap and the trap is active
	TArray<AActor*> overlappingActors;
	DamageBox->GetOverlappingActors(overlappingActors);
	if (TrapActive && overlappingActors.Num() > 0)
	{
		for (AActor* Actor : overlappingActors)
		{
			DealDamage(DeltaTime, Actor);
		}
	}
}

void ATrap_Actor::InitializeTrap()
{
	FTimerHandle handle;
	if (AlwaysActive)
	{
		StartTrap();
	}
	else if (InitialDelay > 0)
	{
		GetWorldTimerManager().SetTimer(TrapTimer, this, &ATrap_Actor::StartTrap, TrapTime, true, InitialDelay);
	}
	else
	{
		GetWorldTimerManager().SetTimer(TrapTimer, this, &ATrap_Actor::StartTrap, TrapTime, true, 0.0f);
	}
}

void ATrap_Actor::StartTrap_Implementation()
{
	// This should get shutoff by the animation
	TrapActive = true;
}

void ATrap_Actor::DealDamage_Implementation(float DeltaTime, AActor* Actor)
{
	// See if we should deal damage again
	if (TimeSinceLastDamage > 0.1f)
	{
		FDamageEventExtended test;
		test.ActiveNormalMods.Add(EModifierType::ENone);
		test.ActiveSecretMods.Add(ESecretModifierType::ENone);
		
		Actor->TakeDamage(BaseDamage, test, nullptr, this);
		TimeSinceLastDamage = 0.0f;
	}
	else
	{
		TimeSinceLastDamage = TimeSinceLastDamage + DeltaTime;
	}
}

void ATrap_Actor::StopTrap_Implementation()
{
	GetWorldTimerManager().ClearTimer(TrapTimer);
}

void ATrap_Actor::OnDamageBoxBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	// Other Actor is the actor that triggered the event. Check that is not ourself.  
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		//ActorToDamage = OtherActor;
	}
}

void ATrap_Actor::OnDamageBoxEndOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//ActorToDamage = nullptr;
}
