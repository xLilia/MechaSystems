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
	TArray<AActor*> ChildCompList;
	GetAttachedActors(ChildCompList);
	MechaComponentsList.Empty();
	for (AActor* Comps : ChildCompList)
	{
		TArray<UMechaComponent*> CompsList;
		Comps->GetComponents(CompsList,true);
		if (CompsList.Num() > 0) {
			for (UMechaComponent* MechaComp : CompsList) {
				MechaComponentsList.Add(MechaComp);
			}
		}
	}
	return MechaComponentsList;
}

