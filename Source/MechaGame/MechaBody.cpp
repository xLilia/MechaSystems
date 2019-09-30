// Fill out your copyright notice in the Description page of Project Settings.


#include "MechaBody.h"

// Sets default values
AMechaBody::AMechaBody()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMechaBody::BeginPlay()
{
	Super::BeginPlay();
	UpdateMechaComponents();
}

// Called every frame
void AMechaBody::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMechaBody::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

TArray<UMechaComponent*> AMechaBody::UpdateMechaComponents()
{
	MechaComponentsList.Empty();
	for (AActor* Ch : Children) {
		TArray<UMechaComponent*> CompsList;
		Ch->GetComponents(CompsList, false);
		if (CompsList[0] != nullptr) {
			CompsList[0]->UpdateSockets();
			MechaComponentsList.Add(CompsList[0]);
		}
	}
	return MechaComponentsList;
}