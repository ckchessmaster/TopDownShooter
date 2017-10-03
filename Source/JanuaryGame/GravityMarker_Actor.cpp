// Fill out your copyright notice in the Description page of Project Settings.

#include "JanuaryGame.h"
#include "GravityMarker_Actor.h"


// Sets default values
AGravityMarker_Actor::AGravityMarker_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGravityMarker_Actor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGravityMarker_Actor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

