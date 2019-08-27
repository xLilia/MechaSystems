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

