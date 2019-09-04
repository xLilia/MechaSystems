// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "CamScreen.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MECHAGAME_API UCamScreen : public UActorComponent
{
	GENERATED_BODY()

	//UPROPERTY(VisibleAnywhere, Category = "CamScreen")
	//	class USceneCaptureComponent2D* RenderTarget;

	UPROPERTY(EditAnywhere, Category = "CamScreen")
		class UMaterialInterface* RenderTargetMaterial;

	UPROPERTY(VisibleAnywhere, Category = "CamScreen")
		class UMaterialInstanceDynamic* RenderTargetMaterialInstance;

public:	
	// Sets default values for this component's properties
	UCamScreen();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "CamScreen")
		void Init(FVector2D Resolution, USceneCaptureComponent2D* RenderTarget, UPrimitiveComponent* ScreenSurface);
		
};
