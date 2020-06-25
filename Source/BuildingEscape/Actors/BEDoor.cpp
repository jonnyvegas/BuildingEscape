// Fill out your copyright notice in the Description page of Project Settings.


#include "BEDoor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/TriggerVolume.h"
#include "BEPressurePlate.h"

// Sets default values
ABEDoor::ABEDoor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Comp"));
	RootComponent = SceneComp;

	DoorMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh"));
	DoorMeshComp->SetupAttachment(RootComponent);

	DoorFrameComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Frame Mesh"));
	DoorFrameComp->SetupAttachment(RootComponent);

	DoorRotation = FRotator(FRotator::ZeroRotator);
	YawToAdd = 90.f;
	TargetYaw = 0.f;
	CurrentYaw = 0.f;
	OpenDoorRotationRate = 0.1f;
	CloseDoorRotationRate = 0.1f;
	InitialYaw = 0.f;
	DoorLastOpened = 0.f;
	DoorDelay = 2.f;
	bOpenDoor = false;
	ItemWeightThreshold = 200.f;
}

// Called when the game starts or when spawned
void ABEDoor::BeginPlay()
{
	Super::BeginPlay();
	if (PressurePlate)
	{
		PressurePlate->ItemsWeightChangedDel.AddDynamic(this, &ABEDoor::SetOpenOrClose);
	}
	if (DoorMeshComp)
	{
		DoorRotation = DoorMeshComp->GetComponentRotation();
		CurrentYaw = DoorRotation.Yaw;
		InitialYaw = CurrentYaw;
		TargetYaw = CurrentYaw + YawToAdd;
		//DoorMeshComp->SetWorldRotation(FRotator(DoorRotation.Pitch, DoorRotation.Yaw + 90.f, DoorRotation.Roll));
	}
	
}

// Called every frame
void ABEDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	OpenOrCloseDoor(DeltaTime, bOpenDoor);
// 	if (PressurePlate)
// 	{
// 		PressurePlate->GetOverlappingActors(OverlappingActors, ActorSubclass);
// 		if (OverlappingActors.Num() > 0)
// 		{
// 			for (AActor* Actor : OverlappingActors)
// 			{
// 				PawnToCheck = Cast<APawn>(Actor);
// 				if (PawnToCheck)
// 				{
// 					OpenOrCloseDoor(DeltaTime, true);
// 					DoorLastOpened = GetWorld()->GetTimeSeconds();
// 					break;
// 				}
// 			}
// 		}
// 		else
// 		{
// 			if (GetWorld()->GetTimeSeconds() - DoorLastOpened >= DoorDelay)
// 			{
// 				OpenOrCloseDoor(DeltaTime, false);
// 				//break;
// 			}
// 		}
// 	}
}

void ABEDoor::OpenOrCloseDoor(float DeltaTime, bool bOpen)
{
	if (bOpen)
	{
		CurrentYaw = FMath::Lerp(CurrentYaw, TargetYaw, DeltaTime * OpenDoorRotationRate);
	}
	else
	{
		CurrentYaw = FMath::Lerp(CurrentYaw, InitialYaw, DeltaTime * CloseDoorRotationRate);
	}
	if (DoorMeshComp)
	{
		//DoorRotation = DoorMeshComp->GetComponentRotation();
		DoorMeshComp->SetWorldRotation(FRotator(DoorRotation.Pitch, CurrentYaw, DoorRotation.Roll));
	}
}

void ABEDoor::SetOpenOrCloseGivenWeight(float ItemsWeight)
{
	bOpenDoor = ItemsWeight >= ItemWeightThreshold;
}
