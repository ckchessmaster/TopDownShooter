// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Globals.generated.h"

UCLASS()
class JANUARYGAME_API UGlobals : public UObject
{
	GENERATED_BODY()



public:

	// Load Blueprint from path (there must be one already in the level, also might not work with packaged project, need to fix this later)
	static FORCEINLINE UBlueprint* LoadBlueprintFromPath(const FName& Path)
	{
		if (Path == NAME_None) return NULL;

		//FString finalPath = RootPath + Path.ToString();

		FStringAssetReference Blueprint(Path.ToString());
		UObject* Object = Blueprint.ResolveObject();

		return Cast<UBlueprint>(Object);
	}

	// Multi Sphere Trace
	static FORCEINLINE bool SphereTraceMulti(TArray<FHitResult> &OutHits, TArray<AActor*> ActorsToIgnore, FVector Start, FVector End, UWorld* World, float Radius, bool DrawTrace)
	{
		// Make sure the world exists
		if (World)
		{
			FCollisionQueryParams traceParams(FName(TEXT("SphereTraceMulti")));
			traceParams.bTraceComplex = true;
			traceParams.bReturnPhysicalMaterial = false;
			traceParams.AddIgnoredActors(ActorsToIgnore);

			// Draw the trace
			if (DrawTrace)
			{
				const FName traceTag("TraceTag");
				World->DebugDrawTraceTag = traceTag;
				traceParams.TraceTag = traceTag;
			}

			// Run trace
			bool foundHit = World->SweepMultiByChannel(OutHits, Start, End + FVector(0, 0, 1), FQuat(), ECollisionChannel::ECC_Visibility, FCollisionShape::MakeSphere(Radius), traceParams);

			return foundHit;
		}

		return false;
	}

	// The path of the game
	static const FString RootPath;
};
