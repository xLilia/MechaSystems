// Fill out your copyright notice in the Description page of Project Settings.


#include "MechaSocket.h"

// Sets default values for this component's properties
UMechaSocket::UMechaSocket()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


UMechaSocket::UMechaSocket(FString Type) : Type(Type)
{

}

// Called when the game starts
void UMechaSocket::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMechaSocket::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}



