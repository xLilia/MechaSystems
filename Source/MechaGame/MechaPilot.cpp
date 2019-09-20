// Fill out your copyright notice in the Description page of Project Settings.


#include "MechaPilot.h"

// Sets default values
AMechaPilot::AMechaPilot()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->bUsePawnControlRotation = true;
	PlayerCamera->SetRelativeLocation(FVector(0, 90, 0));

	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	CameraSpringArm->TargetArmLength = 0;

	CameraSpringArm->SetupAttachment(GetRootComponent());
	PlayerCamera->SetupAttachment(CameraSpringArm);
	
}

// Called when the game starts or when spawned
void AMechaPilot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMechaPilot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMechaPilot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMechaPilot::LookX(float MouseX, float SpeedX)
{
	this->AddControllerYawInput(MouseX * SpeedX);
}

void AMechaPilot::LookY(float MouseY, float SpeedY)
{
	this->AddControllerPitchInput(MouseY * SpeedY);
}

void AMechaPilot::MoveForward(float Speed)
{
	this->AddMovementInput(this->GetArrowComponent()->GetForwardVector(), Speed);
}

void AMechaPilot::MoveRight(float Speed)
{
	this->AddMovementInput(this->GetArrowComponent()->GetRightVector(), Speed);
}

