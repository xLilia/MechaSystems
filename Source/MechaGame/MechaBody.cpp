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
	//TArray<AActor*> ChildCompList;
	//GetAttachedActors(ChildCompList);
	//MechaComponentsList.Empty();
	//for (AActor* Comps : ChildCompList)
	//{
	//	TArray<UMechaComponent*> CompsList;
	//	Comps->GetComponents(CompsList,true);
	//	if (CompsList.Num() > 0) {
	//		for (UMechaComponent* MechaComp : CompsList) {
	//			for (UMechaSocket* Socket : MechaComp->Sockets)
	//			{
	//				if (Socket->Connection != nullptr) {
	//					Socket->Connection->GetOwner()->GetComponents(CompsList, true);
	//				}
	//			}
	//			MechaComponentsList.Add(MechaComp);
	//		}
	//	}
	//}
	//TArray<UMechaComponent*> CompsList;
	//TArray<AActor*> ChildActors;
	//GetAttachedActors(ChildActors);
	//MechaComponentsList.Empty();
	
	//for (AActor* A : ChildActors) {
	//	TArray<AActor*> Childs;
	//	Children
	//	A->GetAttachedActors(Childs);
	//	if()
	//}

	MechaComponentsList.Empty();
	for (AActor* Ch : Children) {
		TArray<UMechaComponent*> CompsList;
		Ch->GetComponents(CompsList, false);
		if (CompsList[0] != nullptr)MechaComponentsList.Add(CompsList[0]);
	}
	return MechaComponentsList;
}