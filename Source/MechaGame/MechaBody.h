// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MechaComponent.h"
#include "MechaBody.generated.h"

UCLASS()
class MECHAGAME_API AMechaBody : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMechaBody();

	UPROPERTY(VisibleAnywhere, Category="MechaBody/Components")
		TArray<class UMechaComponent*> MechaComponentsList;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "MechaBody/Components")
		TArray<class UMechaComponent*> UpdateMechaComponents();

};
