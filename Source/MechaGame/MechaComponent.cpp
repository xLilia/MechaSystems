// Fill out your copyright notice in the Description page of Project Settings.


#include "MechaComponent.h"

// Sets default values for this component's properties
UMechaComponent::UMechaComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMechaComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMechaComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

int UMechaComponent::Connect(UMechaComponent* Other, int32 ThisSocketID, int32 OtherSocketID)
{
	if (this->Sockets[ThisSocketID]->Type == Other->Sockets[OtherSocketID]->Type) {
		Other->Sockets[OtherSocketID]->Connection = this;
		Other->Sockets[OtherSocketID]->ConnectionSocketID = ThisSocketID;
		this->Sockets[ThisSocketID]->Connection = Other;
		this->Sockets[ThisSocketID]->ConnectionSocketID = OtherSocketID;
		return 0;
	}
	return -1;
}

int UMechaComponent::Disconnect(int32 socketID)
{
	if (this->Sockets[socketID]->Connection == nullptr) {
		return 0;
	}
	else if (this->Sockets[socketID]->Connection != nullptr) {
		this->Sockets[socketID]->Connection->Disconnect(this->Sockets[socketID]->ConnectionSocketID);
		this->Sockets[socketID]->ConnectionSocketID = -1;
		this->Sockets[socketID]->Connection = nullptr;
		return 1;
	}
	else {
		return -1;
	}
}

