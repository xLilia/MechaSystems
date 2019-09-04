// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "MechaBody.h"
#include "MechaComponent.h"
#include "VerticalCamera.generated.h"

UCLASS()
class MECHAGAME_API AVerticalCamera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVerticalCamera();

	UPROPERTY(VisibleAnywhere, Category="VerticalCamera/Edit")
		class AMechaBody* SelectedMecha;

	UPROPERTY(VisibleAnywhere, Category = "VerticalCamera/Edit")
		int32 SelectedMechaComponentID = 0;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category="VerticalCamera/Movement")
		void MoveZ(float val, float mult);

	UFUNCTION(BlueprintCallable, Category = "VerticalCamera/Movement")
		void RotateZ(float val, float mult);

	UFUNCTION(BlueprintCallable, Category = "VerticalCamera/Movement")
		void PitchCamera(float val, float mult);

	UFUNCTION(BlueprintCallable, Category = "VerticalCamera/Movement")
		void ZoomOutSpringArm(float val, float mult, class USpringArmComponent* SpringArm);

	UFUNCTION(BlueprintCallable, Category = "VerticalCamera/Movement")
		class AActor* SetTarget(AActor* Target);

	UFUNCTION(BlueprintCallable, Category = "VerticalCamera/Movement")
		class AActor* AlignWithTarget(AActor* Target, FVector mult);

	UFUNCTION(BlueprintCallable, Category = "VerticalCamera/Edit")
		class AMechaBody* SelectMechaBody(class AMechaBody* Mecha);

	UFUNCTION(BlueprintCallable, Category = "VerticalCamera/Edit")
		class UMechaComponent* SelectMechaComponentID(int32 ID);

	UFUNCTION(BlueprintCallable, Category = "VerticalCamera/Edit")
		class UMechaComponent* ScrollMechaComponentID(int32 num);

};
