// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "MechaSocket.h"
#include "MechaComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MECHAGAME_API UMechaComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMechaComponent();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "MechaComponent")
		TArray<class UMechaSocket*> Sockets;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "MechaComponent/MechaGraph")
		int32 GraphLayer = 0;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "MechaComponent")
		bool isSelected = false;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "MechaComponent")
		TArray<class UMechaSocket*> UpdateSockets();

	UFUNCTION(BlueprintCallable, Category="MechaComponent")
		int32 Connect(UMechaComponent* Other, int32 ThisSocketID, int32 OtherSocketID);

	UFUNCTION(BlueprintCallable, Category = "MechaComponent")
		int32 Disconnect(int32 socketID, bool OtherDisconnected);

	UFUNCTION(BlueprintCallable, Category = "MechaComponent")
		FString DisconnectAll();


};
