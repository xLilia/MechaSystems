// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionEventTrigger.h"

// Sets default values for this component's properties
UInteractionEventTrigger::UInteractionEventTrigger()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractionEventTrigger::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInteractionEventTrigger::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInteractionEventTrigger::TriggerInteractionEvent(FString Event, AActor* Instigator)
{
	OnInteractionEvent.Broadcast(Event, Instigator);
}


