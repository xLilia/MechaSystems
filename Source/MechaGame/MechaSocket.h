// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "MechaComponent.h"
#include "MechaSocket.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MECHAGAME_API UMechaSocket : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMechaSocket();
	UMechaSocket(FString Type);

	UPROPERTY()
		FString Type;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="MechaSocket")
		class UMechaComponent* Connection;

	UPROPERTY()
		int32 ConnectionSocketID = -1;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
