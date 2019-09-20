// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "EventVolume.generated.h"

/**
 * 
 */
UCLASS()
class MECHAGAME_API AEventVolume : public ATriggerVolume
{
	GENERATED_BODY()
	
public:

	AEventVolume();

	UFUNCTION(BlueprintCallable, Category = "EventVolume")
		void OnOverlap(AActor* OtherActor);
};
