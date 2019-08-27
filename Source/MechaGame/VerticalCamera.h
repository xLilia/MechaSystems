// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "VerticalCamera.generated.h"

UCLASS()
class MECHAGAME_API AVerticalCamera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVerticalCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category="CameraPawn")
		void MoveZ(float val, float mult);

	UFUNCTION(BlueprintCallable, Category = "CameraPawn")
		void RotateZ(float val, float mult);

	UFUNCTION(BlueprintCallable, Category = "CameraPawn")
		void PitchCamera(float val, float mult);

	UFUNCTION(BlueprintCallable, Category = "CameraPawn")
		void ZoomOutSpringArm(float val, float mult, USpringArmComponent* SpringArm);
};
