// Fill out your copyright notice in the Description page of Project Settings.

#include "VerticalCamera.h"

// Sets default values
AVerticalCamera::AVerticalCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AVerticalCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVerticalCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVerticalCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AVerticalCamera::MoveZ(float val, float mult)
{
	this->AddActorWorldTransform(FTransform(FVector(0, 0, val * mult)));
}

void AVerticalCamera::RotateZ(float val, float mult)
{
	this->AddActorWorldRotation(FRotator(0, val*mult, 0));
}

void AVerticalCamera::PitchCamera(float val, float mult)
{	
	this->AddActorLocalRotation(FRotator(-val * mult, 0, 0));
	FRotator actr = this->GetActorRotation();
	this->SetActorRotation(FRotator(actr.Pitch, actr.Yaw, 0));
}

void AVerticalCamera::ZoomOutSpringArm(float val, float mult, USpringArmComponent* SpringArm)
{
	if (SpringArm == nullptr) return;
	SpringArm->TargetArmLength -= val * mult;
}

AActor* AVerticalCamera::SetTarget(AActor* Target)
{
	if (Target == nullptr) return nullptr;
	FVector OffsetLoc = Target->GetActorTransform().GetLocation() - this->GetActorTransform().GetLocation();
	this->AddActorWorldTransform(FTransform(OffsetLoc));
	return Target;
}

void AVerticalCamera::SetTargetByPos(FVector Target)
{
	FVector OffsetLoc = Target - this->GetActorTransform().GetLocation();
	this->AddActorWorldTransform(FTransform(OffsetLoc));
	return;
}

AActor* AVerticalCamera::AlignWithTarget(AActor* Target, FVector mult = FVector(1,1,1))
{
	if (Target == nullptr) return nullptr; 
	SetTarget(Target);
	FRotator rot = Target->GetActorRotation();
	rot.Roll *= mult.X;
	rot.Pitch *= mult.Y;
	rot.Yaw *= mult.Z;
	this->SetActorRotation(rot);
	return Target;
}

AMechaBody* AVerticalCamera::SelectMechaBody(AMechaBody* Mecha)
{
	SelectedMecha = Mecha;
	if (Mecha == nullptr || SelectedMecha->MechaComponentsList.Num() == 0) return nullptr;
	SelectedMechaComponentID = 0;
	SelectedMechaComponentSocketID = 0;
	return SelectedMecha;
}

UMechaComponent* AVerticalCamera::SelectMechaComponentID(int32 ID)
{
	if (SelectedMecha == nullptr || SelectedMecha->MechaComponentsList.Num() == 0) return nullptr;
	UMechaComponent* MC = SelectedMecha->MechaComponentsList[ID];
	UMechaComponent* OldMC = SelectedMecha->MechaComponentsList[SelectedMechaComponentID];
	OldMC->isComponentSelected = false;
	MC->isComponentSelected = true;
	SetTarget(MC->GetOwner());
	SelectedMechaComponentID = ID;
	SelectedMechaComponentSocketID = 0;
	return MC;
}

UMechaComponent* AVerticalCamera::SelectMechaComponentClick()
{
	if (SelectedMecha == nullptr || SelectedMecha->MechaComponentsList.Num() == 0) return nullptr;
	FVector WorldPos, WorldDir;
	if (GetWorld()->GetFirstPlayerController()->DeprojectMousePositionToWorld(WorldPos, WorldDir)) {
		FHitResult hit;
		//DrawDebugLine(GetWorld(), WorldPos,WorldPos+WorldDir*1000, FColor::Red,true,-1,(uint8)'\000',1);
		if (GetWorld()->LineTraceSingleByChannel(hit, WorldPos, WorldPos + WorldDir * 1000, ECollisionChannel::ECC_WorldDynamic)) {
			if (hit.bBlockingHit) {
				//DrawDebugSphere(GetWorld(), hit.ImpactPoint, 5, 6, FColor::Green, false, -1, (uint8)'\000', 1);
				TArray<UMechaComponent*> MCc;
				hit.GetActor()->GetComponents(MCc, true);
				if (MCc.Num() > 0) {
					return SelectMechaComponentID(SelectedMecha->MechaComponentsList.Find(MCc[0]));
				}
			}
			
		}
	}
	return SelectMechaComponentID(0);
}

UMechaComponent* AVerticalCamera::ScrollMechaComponent(int32 num)
{
	if (SelectedMecha == nullptr || SelectedMecha->MechaComponentsList.Num() == 0) return nullptr;
	int32 max = SelectedMecha->MechaComponentsList.Num();
	return SelectMechaComponentID((SelectedMechaComponentID + num) % max);
}

UMechaSocket* AVerticalCamera::SelectMechaComponentSocketID(int32 ID)
{
	if (SelectedMecha == nullptr || SelectedMecha->MechaComponentsList.Num() == 0) return nullptr;
	if (SelectedMecha->MechaComponentsList[SelectedMechaComponentID] == nullptr || SelectedMecha->MechaComponentsList[SelectedMechaComponentID]->Sockets.Num() == 0) return nullptr;
	UMechaSocket* MS = SelectedMecha->MechaComponentsList[SelectedMechaComponentID]->Sockets[ID];
	SetTargetByPos(MS->GetComponentLocation());
	SelectedMechaComponentSocketID = ID;
	return MS;
}

UMechaSocket* AVerticalCamera::ScrollMechaComponentSocket(int32 num)
{
	if (SelectedMecha == nullptr || SelectedMecha->MechaComponentsList.Num() == 0) return nullptr;
	if (SelectedMecha->MechaComponentsList[SelectedMechaComponentID] == nullptr || SelectedMecha->MechaComponentsList[SelectedMechaComponentID]->Sockets.Num() == 0) return nullptr;
	int32 max = SelectedMecha->MechaComponentsList[SelectedMechaComponentID]->Sockets.Num();
	return SelectMechaComponentSocketID((SelectedMechaComponentSocketID + num) % max);
}

int32 AVerticalCamera::InstallComponentAtSocket(UMechaComponent* newComponent, UMechaSocket* ComponentSocket)
{
	return newComponent->ConnectToSocket(ComponentSocket); //FLIP componentSide otherSktSIDEtag	
}

TArray<AActor*>& AVerticalCamera::GetMechaComponentActorTreeFrom(UMechaComponent* MechaComponent, TArray<AActor*>& TreeList)
{
	if (SelectedMecha == nullptr)
	if (MechaComponent == nullptr)
	if (MechaComponent->Sockets.Num() > 0) {
		for (UMechaSocket* skt : MechaComponent->Sockets) {
			if (skt->Connection != nullptr) {
				TreeList.Add(skt->Connection->GetOwner());
				GetMechaComponentActorTreeFrom(skt->Connection, TreeList);
			}
		}
	}
	return TreeList;
}

void AVerticalCamera::DestroyMechaComponent(UMechaComponent* MechaComponent)
{

	TArray<AActor*> Tree;
	GetMechaComponentActorTreeFrom(MechaComponent, Tree);

	if (Tree.Num() > 0) for (AActor* A : Tree) { if(A!=Tree[0])A->Destroy();}

	if (MechaComponent->ConnectionSocket != nullptr) MechaComponent->ConnectionSocket->Connection = nullptr;
	MechaComponent->GetOwner()->Destroy();
	SelectedMecha->UpdateMechaComponents();
	
	if (SelectedMecha->MechaComponentsList.Num() == 0) return;
	SelectedMechaComponentID = 0;
	SelectedMechaComponentSocketID = 0;
	//Clamp selectedComponents
	//SelectedMechaComponentID = FMath::Clamp(SelectedMechaComponentID, 0, SelectedMecha->MechaComponentsList.Num() - 1);
	//SelectedMechaComponentID = FMath::Clamp(SelectedMechaComponentID, 0, SelectedMechaComponentID);
	//if (SelectedMecha->MechaComponentsList.Num() == 0) return;
	//SelectedMechaComponentSocketID = FMath::Clamp(SelectedMechaComponentSocketID, 0, SelectedMecha->MechaComponentsList[SelectedMechaComponentID]->Sockets.Num() - 1);
	//SelectedMechaComponentSocketID = FMath::Clamp(SelectedMechaComponentSocketID, 0, SelectedMechaComponentSocketID);
}

void AVerticalCamera::SpawnMechaComponentAtSocket(const TSubclassOf<class AActor> MechaComponent, UMechaSocket* Socket)
{
	if (SelectedMecha == nullptr) return;
	if (Socket == nullptr) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.bNoFail = true;
	SpawnParams.Owner = SelectedMecha;
	SpawnParams.Instigator = SelectedMecha;
	AActor* MechaComponentOwner = GetWorld()->SpawnActor<AActor>(MechaComponent, Socket->GetComponentTransform(), SpawnParams);
	
	TArray<UMechaComponent*> MechaComp;
	MechaComponentOwner->GetComponents(MechaComp, true);
	
	if (MechaComp[0] != nullptr) 
		if (InstallComponentAtSocket(MechaComp[0], Socket) != 1) {
			MechaComponentOwner->Destroy();
			return;
		}

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::KeepWorld, false);
	MechaComponentOwner->AttachToActor(Socket->GetOwner(), AttachmentRules);
	SelectedMecha->UpdateMechaComponents();
}




