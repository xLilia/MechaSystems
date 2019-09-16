// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomMouseInterface.h"

// Sets default values for this component's properties
UCustomMouseInterface::UCustomMouseInterface()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCustomMouseInterface::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UCustomMouseInterface::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCustomMouseInterface::ShowMouse(APlayerController* PC)
{
	PC->bShowMouseCursor = true;
}

void UCustomMouseInterface::HideMouse(APlayerController* PC)
{
	PC->bShowMouseCursor = false;
}

void UCustomMouseInterface::SnapMouseToCenter(APlayerController* PC)
{
	int32 X, Y;
	GetViewportCenter(PC, X, Y);
	PC->SetMouseLocation(X,Y);
}

void UCustomMouseInterface::GetViewportCenter(APlayerController* PC, int32 &X, int32 &Y)
{
	PC->GetViewportSize(X, Y);
	X /= 2;
	Y /= 2;
}

void UCustomMouseInterface::LockMousePosToCoord(APlayerController * PC)
{
	if (!MouseLocked) {
		PC->GetMousePosition(MouseLockedPos.X, MouseLockedPos.Y);
		MouseLocked = true;
	}
	else {
		PC->SetMouseLocation(MouseLockedPos.X, MouseLockedPos.Y);
	}
	
}

void UCustomMouseInterface::UnlockMousePos(APlayerController * PC)
{
		MouseLocked = false;
}

