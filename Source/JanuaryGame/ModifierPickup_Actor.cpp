// Fill out your copyright notice in the Description page of Project Settings.

#include "JanuaryGame.h"
#include "ModifierPickup_Actor.h"


// Sets default values
AModifierPickup_Actor::AModifierPickup_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup the NavigationBox box
	PickupArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Navigation"));
	PickupArea->SetBoxExtent(FVector(64, 64, 64), true);
	RootComponent = PickupArea;
}

// Called when the game starts or when spawned
void AModifierPickup_Actor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AModifierPickup_Actor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

