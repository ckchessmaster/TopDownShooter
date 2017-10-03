// Fill out your copyright notice in the Description page of Project Settings.

#include "JanuaryGame.h"
#include "Enemy_AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Player_Character.h"
#include "Enemy_Character.h"


AEnemy_AIController::AEnemy_AIController()
{
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent")));
	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AEnemy_AIController::SenseStuff);

}

void AEnemy_AIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// If we have an enemy lets go get them!
	if (Enemy)
	{
		GetPawn()->SetActorRelativeRotation(FRotationMatrix::MakeFromX(Enemy->GetActorLocation() - GetPawn()->GetActorLocation()).Rotator(), true, 0);

		AEnemy_Character* enemyConverted = Cast<AEnemy_Character>(GetPawn());
		if (GetPawn()->GetDistanceTo(Enemy) <= enemyConverted->MyWeapon->WeaponConfig.Range)
		{
			enemyConverted->MyWeapon->PrepareFire();
			MoveTo(GetPawn()->GetActorLocation());
		}
		else
		{
			MoveTo(Enemy->GetActorLocation());
		}
	}
}

// returns an array of the new actors that triggered this function
void AEnemy_AIController::SenseStuff(TArray<AActor*> Actors)
{
	// Loop through all sensed actors and if player is there set it as our target enemy
	for (AActor* actor : Actors)
	{	
		APlayer_Character* player = Cast<APlayer_Character>(actor);

		if (player)
		{
			// Ensure that the player is just now being seen and not leaving our sight
			FActorPerceptionBlueprintInfo actorInfo;
			GetPerceptionComponent()->GetActorsPerception(player, actorInfo);
			if (actorInfo.LastSensedStimuli[0].WasSuccessfullySensed())
			{
				Enemy = player;
				return;
			}
			else
			{
				// If we havn't found the player (or the player has gone out of range) set enemy to null
				GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, "we are setting to null!");
				Enemy = nullptr;
				return;
			}
		}
	}

	
}