// Fill out your copyright notice in the Description page of Project Settings.


#include "CamScreen.h"

// Sets default values for this component's properties
UCamScreen::UCamScreen()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCamScreen::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
}


// Called every frame
void UCamScreen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCamScreen::Init(FVector2D Resolution, USceneCaptureComponent2D* RenderTarget, UPrimitiveComponent* ScreenSurface)
{
	if (RenderTarget == nullptr || ScreenSurface == nullptr || RenderTargetMaterial == nullptr) return;
	RenderTarget->TextureTarget = UKismetRenderingLibrary::CreateRenderTarget2D(this, Resolution.X, Resolution.Y);
	RenderTargetMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(this, RenderTargetMaterial);
	RenderTargetMaterialInstance->SetTextureParameterValue("CustomRenderTarget", RenderTarget->TextureTarget);
	ScreenSurface->SetMaterial(0, RenderTargetMaterialInstance);
}

