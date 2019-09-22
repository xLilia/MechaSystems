// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "InteractionEventTrigger.h"
#include "TriggerEventBox.generated.h"

/**
 * 
 */
UCLASS()
class MECHAGAME_API ATriggerEventBox : public ATriggerBox
{
	GENERATED_BODY()

public:
	
	ATriggerEventBox();

	//UFUNCTION(BlueprintCallable)
	//	void CheckInteractionEvents();

};
