// Fill out your copyright notice in the Description page of Project Settings.


#include "VerticalCamera.h"

// Sets default values
AVerticalCamera::AVerticalCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AVerticalCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVerticalCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVerticalCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AVerticalCamera::MoveZ(float val, float mult)
{
	this->AddActorWorldTransform(FTransform(FVector(0, 0, val * mult)));
}

void AVerticalCamera::RotateZ(float val, float mult)
{
	this->AddActorWorldRotation(FRotator(0, val*mult, 0));
}

void AVerticalCamera::PitchCamera(float val, float mult)
{	
	this->AddActorLocalRotation(FRotator(-val * mult, 0, 0));
	FRotator actr = this->GetActorRotation();
	this->SetActorRotation(FRotator(actr.Pitch, actr.Yaw, 0));
}

void AVerticalCamera::ZoomOutSpringArm(float val, float mult, USpringArmComponent* SpringArm)
{
	if (SpringArm == nullptr) return;
	SpringArm->TargetArmLength -= val * mult;
}

AActor* AVerticalCamera::SetTarget(AActor* Target)
{
	if (Target == nullptr) return nullptr;
	FVector OffsetLoc = Target->GetActorTransform().GetLocation() - this->GetActorTransform().GetLocation();
	this->AddActorWorldTransform(FTransform(OffsetLoc));
	return Target;
}


void AVerticalCamera::SetTargetByPos(FVector Target)
{
	FVector OffsetLoc = Target - this->GetActorTransform().GetLocation();
	this->AddActorWorldTransform(FTransform(OffsetLoc));
	return;
}


AActor* AVerticalCamera::AlignWithTarget(AActor* Target, FVector mult = FVector(1,1,1))
{
	if (Target == nullptr) return nullptr; 
	SetTarget(Target);
	FRotator rot = Target->GetActorRotation();
	rot.Roll *= mult.X;
	rot.Pitch *= mult.Y;
	rot.Yaw *= mult.Z;
	this->SetActorRotation(rot);
	return Target;
}


AMechaBody* AVerticalCamera::SelectMechaBody(AMechaBody* Mecha)
{
	SelectedMecha = Mecha;
	if (Mecha == nullptr || SelectedMecha->MechaComponentsList.Num() == 0) return nullptr;
	SelectedMechaComponentID = 0;
	SelectedMechaComponentSocketID = 0;
	return SelectedMecha;
}

UMechaComponent* AVerticalCamera::SelectMechaComponentID(int32 ID)
{
	if (SelectedMecha == nullptr || SelectedMecha->MechaComponentsList.Num() == 0) return nullptr;
	UMechaComponent* MC = SelectedMecha->MechaComponentsList[ID];
	SetTarget(MC->GetOwner());
	SelectedMechaComponentID = ID;
	SelectedMechaComponentSocketID = 0;
	return MC;
}

UMechaComponent* AVerticalCamera::ScrollMechaComponent(int32 num)
{
	if (SelectedMecha == nullptr || SelectedMecha->MechaComponentsList.Num() == 0) return nullptr;
	int32 max = SelectedMecha->MechaComponentsList.Num();
	return SelectMechaComponentID((SelectedMechaComponentID + num) % max);
}

UMechaSocket* AVerticalCamera::SelectMechaComponentSocketID(int32 ID)
{
	if (SelectedMecha == nullptr || SelectedMecha->MechaComponentsList[SelectedMechaComponentID] == nullptr || SelectedMecha->MechaComponentsList[SelectedMechaComponentID]->Sockets.Num() == 0) return nullptr;
	UMechaSocket* MS = SelectedMecha->MechaComponentsList[SelectedMechaComponentID]->Sockets[ID];
	SetTargetByPos(MS->GetComponentLocation());
	SelectedMechaComponentSocketID = ID;
	return MS;
}

UMechaSocket* AVerticalCamera::ScrollMechaComponentSocket(int32 num)
{
	if (SelectedMecha == nullptr || SelectedMecha->MechaComponentsList[SelectedMechaComponentID] == nullptr || SelectedMecha->MechaComponentsList[SelectedMechaComponentID]->Sockets.Num() == 0) return nullptr;
	int32 max = SelectedMecha->MechaComponentsList[SelectedMechaComponentID]->Sockets.Num();
	return SelectMechaComponentSocketID((SelectedMechaComponentSocketID + num) % max);
}


