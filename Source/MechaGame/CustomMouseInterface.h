// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "CustomMouseInterface.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MECHAGAME_API UCustomMouseInterface : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY()
		bool MouseLocked = false;

	UPROPERTY()
		FVector2D MouseLockedPos;
public:	
	// Sets default values for this component's properties
	UCustomMouseInterface();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "CustomMouseInterface")
		void ShowMouse(APlayerController* PC);

	UFUNCTION(BlueprintCallable, Category = "CustomMouseInterface")
		void HideMouse(APlayerController* PC);

	UFUNCTION(BlueprintCallable, Category = "CustomMouseInterface")
		void SnapMouseToCenter(APlayerController* PC);

	UFUNCTION(BlueprintCallable, Category = "CustomMouseInterface")
		void GetViewportCenter(APlayerController* PC, int32 &X, int32 &Y);

	UFUNCTION(BlueprintCallable, Category = "CustomMouseInterface")
		void LockMousePosToCoord (APlayerController* PC);

	UFUNCTION(BlueprintCallable, Category = "CustomMouseInterface")
		void UnlockMousePos(APlayerController* PC);
};
