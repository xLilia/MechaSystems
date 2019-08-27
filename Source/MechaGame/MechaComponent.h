// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MechaSocket.h"
#include "MechaComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MECHAGAME_API UMechaComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMechaComponent();

	UPROPERTY()
		TArray<class UMechaSocket*> Sockets;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category="MechaSockets")
		int Connect(UMechaComponent* Other, int32 ThisSocketID, int32 OtherSocketID);
	UFUNCTION(BlueprintCallable, Category = "MechaSockets")
		int Disconnect(int32 socketID);
		
};
