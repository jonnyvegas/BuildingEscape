// Fill out your copyright notice in the Description page of Project Settings.


#include "BEGrabber.h"
#include "GameFramework/PlayerController.h"
#include "BEPawnNew.h"

// Sets default values for this component's properties
UBEGrabber::UBEGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PawnViewLoc = FVector(FVector::ZeroVector);
	PawnViewRot = FRotator(FRotator::ZeroRotator);
	// ...
}


// Called when the game starts
void UBEGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBEGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	// Get viewpoint
	ABEPawnNew* BEPawn = Cast<ABEPawnNew>(GetOwner());
	if (BEPawn)
	{
		APlayerController* PlayerController = Cast<APlayerController>(BEPawn->GetController());
		if (PlayerController)
		{
			PlayerController->GetActorEyesViewPoint(PawnViewLoc, PawnViewRot);
			UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"), *PawnViewLoc.ToString(), *PawnViewRot.ToString());
		}
	}

	// Line trace to a certain distance (reach) from the viewpoint


}

