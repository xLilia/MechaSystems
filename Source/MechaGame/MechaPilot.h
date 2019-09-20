// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/WorldSettings.h"
#include "Camera/CameraComponent.h"
#include "MechaPilot.generated.h"

UCLASS()
class MECHAGAME_API AMechaPilot : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMechaPilot();
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MechaPilot/Components")
		class UCameraComponent* PlayerCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MechaPilot/Components")
		class USpringArmComponent* CameraSpringArm;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION(BlueprintCallable, Category = "MechaPilot/Control")
		void LookX(float MouseX, float SpeedX = 1);

	UFUNCTION(BlueprintCallable, Category = "MechaPilot/Control")
		void LookY(float MouseY, float SpeedY = 1);

	UFUNCTION(BlueprintCallable, Category = "MechaPilot/Control")
		void MoveForward(float Speed);
	
	UFUNCTION(BlueprintCallable, Category = "MechaPilot/Control")
		void MoveRight(float Speed);
};
