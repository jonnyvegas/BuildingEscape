// Fill out your copyright notice in the Description page of Project Settings.


#include "BEDoor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"

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
}

// Called when the game starts or when spawned
void ABEDoor::BeginPlay()
{
	Super::BeginPlay();
	
	if (DoorMeshComp)
	{
		DoorRotation = DoorMeshComp->GetComponentRotation();
		DoorMeshComp->SetWorldRotation(FRotator(DoorRotation.Pitch, DoorRotation.Yaw + 90.f, DoorRotation.Roll));
	}
}

// Called every frame
void ABEDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

