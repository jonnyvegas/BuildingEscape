// Fill out your copyright notice in the Description page of Project Settings.


#include "BEPawnNew.h"
#include "BEGrabber.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/CapsuleComponent.h"
#include "Components/SceneComponent.h"

// Sets default values
ABEPawnNew::ABEPawnNew()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	GrabberComp = CreateDefaultSubobject<UBEGrabber>(TEXT("Grabber"));
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
 	FloatingMovementComp = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingMovementComp"));
  	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollisionComp"));
	
	RootComponent = CapsuleComp;

	StaticMeshComp->SetupAttachment(RootComponent);
	//CapsuleComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABEPawnNew::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABEPawnNew::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABEPawnNew::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ABEPawnNew::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABEPawnNew::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ABEPawnNew::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookRight", this, &ABEPawnNew::AddControllerYawInput);

}

void ABEPawnNew::MoveForward(float Val)
{
	AddMovementInput(GetActorForwardVector(), Val);
}

void ABEPawnNew::MoveRight(float Val)
{
	AddMovementInput(GetActorRightVector(), Val);
}

