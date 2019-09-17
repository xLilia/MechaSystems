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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MechaSocket")
		FString Type;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="MechaSocket")
		class UMechaComponent* Connection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MechaSocket")
		int32 ConnectionSocketID = -1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MechaSocket")
		int32 ComponentSocketID = -1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MechaSocket")
		int32 GraphLayer = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MechaSocket")
		int32 GraphLayerOffset = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MechaSocket")
		FVector2D GraphPos2D;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	

};
