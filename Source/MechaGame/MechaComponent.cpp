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

TArray<class UMechaSocket*> UMechaComponent::UpdateSockets()
{
	Sockets.Empty();
	GetOwner()->GetComponents(Sockets, true);
	int32 sID = 0;
	for (UMechaSocket* Socket : Sockets)
	{
		Socket->ComponentSocketID = sID;
		Socket->GraphLayerOffset = Socket->GraphLayer + this->GraphLayer;
	}
	return Sockets;
}

int32 UMechaComponent::Connect(UMechaComponent* Other, int32 ThisSocketID, int32 OtherSocketID)
{
	if (Other == nullptr) return -1;
	if (this->Sockets[ThisSocketID]->Type == Other->Sockets[OtherSocketID]->Type) {
		Other->Sockets[OtherSocketID]->Connection = this;
		Other->Sockets[OtherSocketID]->ConnectionSocketID = ThisSocketID;
		this->Sockets[ThisSocketID]->Connection = Other;
		this->Sockets[ThisSocketID]->ConnectionSocketID = OtherSocketID;
		return 1;
	}
	return 0;
}

int32 UMechaComponent::Disconnect(int32 socketID)
{
	if (this->Sockets.Num() == 0) return 0;
	if (this->Sockets[socketID]->Connection == nullptr) return -1;
	
	UMechaComponent* Con = this->Sockets[socketID]->Connection;
	this->Sockets[socketID]->Connection = nullptr;
	this->Sockets[socketID]->ConnectionSocketID = -1;
	if (this->Sockets[socketID]->Connection->Sockets[this->Sockets[socketID]->ConnectionSocketID]->ConnectionSocketID != -1)
		Con->Disconnect(this->Sockets[socketID]->ConnectionSocketID);
	
	return 1;
}

FString UMechaComponent::DisconnectAll()
{
	if (this->Sockets.Num() == 0) return "empty";

	FString status;
	int32 id = 0;
	for (UMechaSocket* skt : Sockets) {
		status += FString().FromInt(Disconnect(id++));
	}

	return status;
}
