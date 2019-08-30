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
	SpringArm->TargetArmLength -= val * mult;
}

void AVerticalCamera::SetTarget(AActor* Target)
{
	FVector OffsetLoc = Target->GetActorTransform().GetLocation() - this->GetActorTransform().GetLocation();
	this->AddActorWorldTransform(FTransform(OffsetLoc));
}

void AVerticalCamera::SelectMechaBody(AMechaBody* Mecha)
{
	SelectedMecha = Mecha;
	if (Mecha == nullptr) return;
	if (SelectedMecha->MechaComponentsList.Num() == 0)return;
	SetTarget(Mecha->MechaComponentsList[0]->GetOwner());
	SelectedMechaComponentID = 0;
}

void AVerticalCamera::SelectMechaComponentID(int32 ID)
{
	if (SelectedMecha == nullptr) return;
	if (SelectedMecha->MechaComponentsList.Num() == 0)return;
	SetTarget(SelectedMecha->MechaComponentsList[ID]->GetOwner());
	SelectedMechaComponentID = ID;
}

void AVerticalCamera::ScrollMechaComponentID(int32 num)
{
	if (SelectedMecha == nullptr) return;
	if (SelectedMecha->MechaComponentsList.Num() == 0)return;
	int32 max = SelectedMecha->MechaComponentsList.Num();
	SelectMechaComponentID((SelectedMechaComponentID + num) % max);
}

