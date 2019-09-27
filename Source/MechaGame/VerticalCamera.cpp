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
	SetAllSocketsVisiblity(false);
	return SelectedMecha;
}

UMechaComponent* AVerticalCamera::SelectMechaComponentID(int32 ID)
{
	if (SelectedMecha == nullptr || SelectedMecha->MechaComponentsList.Num() == 0 || ID < 0 || ID > SelectedMecha->MechaComponentsList.Num()) return nullptr;
	UMechaComponent* MC = SelectedMecha->MechaComponentsList[ID];
	UMechaComponent* OldMC = SelectedMecha->MechaComponentsList[SelectedMechaComponentID];
	OldMC->isComponentSelected = false;
	MC->isComponentSelected = true;
	SetSocketsVisiblity(OldMC, false);
	SetSocketsVisiblity(MC, true);
	SetTarget(MC->GetOwner());
	SelectedMechaComponentID = ID;
	SelectedMechaComponentSocketID = 0;
	return MC;
}

UMechaComponent* AVerticalCamera::ScrollMechaComponent(int32 num)
{
	if (SelectedMecha == nullptr || SelectedMecha->MechaComponentsList.Num() == 0) return nullptr;
	return SelectMechaComponentID((SelectedMechaComponentID + num) % SelectedMecha->MechaComponentsList.Num());
}

UMechaSocket* AVerticalCamera::SelectMechaComponentSocketID(int32 ID)
{
	if (SelectedMecha == nullptr || SelectedMecha->MechaComponentsList.Num() == 0 || ID < 0 ) return nullptr;
	if (SelectedMecha->MechaComponentsList[SelectedMechaComponentID] == nullptr || SelectedMecha->MechaComponentsList[SelectedMechaComponentID]->Sockets.Num() == 0) return nullptr;
	if (ID > SelectedMecha->MechaComponentsList[SelectedMechaComponentID]->Sockets.Num()) return nullptr;
	UMechaSocket* MS = SelectedMecha->MechaComponentsList[SelectedMechaComponentID]->Sockets[ID];
	SetTargetByPos(MS->GetComponentLocation());
	SelectedMechaComponentSocketID = ID;
	return MS;
}

UMechaSocket* AVerticalCamera::ScrollMechaComponentSocket(int32 num)
{
	if (SelectedMecha == nullptr || SelectedMecha->MechaComponentsList.Num() == 0) return nullptr;
	if (SelectedMecha->MechaComponentsList[SelectedMechaComponentID] == nullptr || SelectedMecha->MechaComponentsList[SelectedMechaComponentID]->Sockets.Num() == 0) return nullptr;
	return SelectMechaComponentSocketID((SelectedMechaComponentSocketID + num) % SelectedMecha->MechaComponentsList[SelectedMechaComponentID]->Sockets.Num());
}

UActorComponent* AVerticalCamera::SelectMechaComponentSocketClick() {
	if (SelectedMecha == nullptr || SelectedMecha->MechaComponentsList.Num() == 0) return nullptr;
	FVector WorldPos, WorldDir;
	if (GetWorld()->GetFirstPlayerController()->DeprojectMousePositionToWorld(WorldPos, WorldDir)) {
		FHitResult hit;
		//DrawDebugLine(GetWorld(), WorldPos,WorldPos+WorldDir*1000, FColor::Red,true,-1,(uint8)'\000',1);
		if (GetWorld()->LineTraceSingleByChannel(hit, WorldPos, WorldPos + WorldDir * 1000, ECollisionChannel::ECC_WorldDynamic)) {
			if (hit.bBlockingHit) {
				//DrawDebugSphere(GetWorld(), hit.ImpactPoint, 10, 12, FColor::Green, true, -1, (uint8)'\000', .5);
				TArray<UMechaComponent*> MCc;
				hit.GetActor()->GetComponents(MCc, false);
				if (MCc.Num() > 0) {
					return SelectMechaComponentID(SelectedMecha->MechaComponentsList.Find(MCc[0]));
				}
				else
				if (UMechaSocket * s = Cast<UMechaSocket>(hit.Actor->GetComponentByClass(UMechaSocket::StaticClass()))) {
					return SelectMechaComponentSocketID(SelectedMecha->MechaComponentsList[SelectedMechaComponentID]->Sockets.Find(s));
				}
			}
		}
	}
	SetAllSocketsVisiblity(false);
	return SelectMechaComponentID(0);
}

//Create Component Tree from Socket Connections
TArray<AActor*>& AVerticalCamera::GetMechaComponentActorTreeFrom(UMechaComponent* MechaComponent, TArray<AActor*>& TreeList)
{
	if (SelectedMecha != nullptr) 
	if (MechaComponent != nullptr)
	if (MechaComponent->Sockets.Num() > 0) {
		for (UMechaSocket* skt : MechaComponent->Sockets) {
			if (skt->Connection != nullptr) {
				DrawDebugSphere(GetWorld(), skt->Connection->GetOwner()->GetActorLocation(), 10, 12, FColor::Red, true, -1, (uint8)'\000', .5);
				TreeList.Add(skt->Connection->GetOwner());
				GetMechaComponentActorTreeFrom(skt->Connection, TreeList);
			}
		}
	}
	return TreeList;
}

void AVerticalCamera::DestroyMechaComponent(UMechaComponent* MechaComponent)
{
	//If last component return
	if (SelectedMecha->MechaComponentsList.Num() == 1) return;
	
	//Fetch & Destroy component Tree
	TArray<AActor*> Tree;
	GetMechaComponentActorTreeFrom(MechaComponent, Tree);
	if (Tree.Num() > 0) for (AActor* A : Tree) { A->Destroy();} 

	//Clear Connection Socket Connection
	if (MechaComponent->ConnectionSocket != nullptr) MechaComponent->ConnectionSocket->Connection = nullptr; 
	MechaComponent->GetOwner()->Destroy();

	SelectedMecha->UpdateMechaComponents();
	
	//Reset Selection IDs
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

int32 AVerticalCamera::InstallComponentAtSocket(UMechaComponent* newComponent, UMechaSocket* ComponentSocket)
{
	return newComponent->ConnectToSocket(ComponentSocket); //FLIP componentSide otherSktSIDEtag	
}

void AVerticalCamera::SpawnMechaComponentAtSocket(const TSubclassOf<class AActor> MechaComponent, UMechaSocket* Socket)
{
	if (SelectedMecha == nullptr) return;
	if (Socket == nullptr) return;
	//DefineSpawnParameters
	FActorSpawnParameters SpawnParams;
	SpawnParams.bNoFail = true;
	SpawnParams.Owner = SelectedMecha;
	SpawnParams.Instigator = SelectedMecha;
	//Create actor @ Socket
	AActor* MechaComponentOwner = GetWorld()->SpawnActor<AActor>(MechaComponent, Socket->GetComponentTransform(), SpawnParams); 
	//fetch component from actor
	UMechaComponent* MechaComp = Cast<UMechaComponent>(MechaComponentOwner->GetComponentByClass(UMechaComponent::StaticClass()));
	//Setup Socket connection
	if (MechaComp != nullptr) 
		if (InstallComponentAtSocket(MechaComp, Socket) != 1) {
			MechaComponentOwner->Destroy(); //Destroy actor if Socket Occupied
			return;
		}
	//Attach new Actor to Socket
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::KeepWorld, false);
	MechaComponentOwner->AttachToActor(Socket->GetOwner(), AttachmentRules);
	SelectedMecha->UpdateMechaComponents();
	SelectMechaComponentID(SelectedMecha->MechaComponentsList.Find(MechaComp));
}

void AVerticalCamera::SetSocketsVisiblity(UMechaComponent* MechaComponent, bool Visibility)
{
	for (auto s : MechaComponent->Sockets) {
		s->GetOwner()->SetActorHiddenInGame(!Visibility);
	}
}

void AVerticalCamera::SetAllSocketsVisiblity(bool Visibility)
{
	for (auto mc : this->SelectedMecha->MechaComponentsList) {
		SetSocketsVisiblity(mc, Visibility);
	}
}




