// Fill out your copyright notice in the Description page of Project Settings.


#include "BEGrabber.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Pawn.h"
#include "BEPawnNew.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/PrimitiveComponent.h"
#include "BEPawnNew.h"

// Sets default values for this component's properties
UBEGrabber::UBEGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PawnViewLoc = FVector(FVector::ZeroVector);
	PawnViewRot = FRotator(FRotator::ZeroRotator);
	ViewRotToVector = FVector(FVector::ZeroVector);
	TraceDistance = 1000.f;
	
	// Cheating!
	TracingType = UEngineTypes::ConvertToTraceType(ECC_Visibility);

	QueryParams = FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody);

	CollisionParams = FCollisionQueryParams(FName(""), false);
	PhysicsHandleComp = nullptr;
	BEPawn = nullptr;

	// ...
}


// Called when the game starts
void UBEGrabber::BeginPlay()
{
	Super::BeginPlay();
	if (GetOwner())
	{
		ActorsToIgnore.AddUnique(GetOwner());
		BEPawn = Cast<ABEPawnNew>(GetOwner());
		CollisionParams = FCollisionQueryParams(NAME_None, false, BEPawn);
		if (PhysicsHandleClass)
		{
			PhysicsHandleComp = Cast<UPhysicsHandleComponent>(BEPawn->GetComponentByClass(PhysicsHandleClass));
		}
	}
}


// Called every frame
void UBEGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	HandlePhysicsComp(DeltaTime);
}

void UBEGrabber::GrabItem()
{
	// So you want to grab an item eh?
	// Let's see if we hit anything.
	if (TraceForHit(HitResult) && PhysicsHandleComp && PrimitiveCompClass)
	{
		// Cool, grab it.
		PhysicsHandleComp->GrabComponentAtLocation(HitResult.GetComponent(), NAME_None, GetLineTraceEnd());
	}
}

void UBEGrabber::ReleaseItem()
{
	// If we have an item and the physics handle component is valid...
	// Release the hounds! er... the item.
	if (PhysicsHandleComp)
	{
		PhysicsHandleComp->ReleaseComponent();
	}
}

FVector UBEGrabber::GetLineTraceEnd()
{
	PawnViewLoc = BEPawn->GetPawnViewLocation();
	PawnViewRot = BEPawn->GetViewRotation();
	ViewRotToVector = PawnViewRot.Vector();
	ViewRotToVector.Normalize();
	return PawnViewLoc + (ViewRotToVector * TraceDistance);
}

UPrimitiveComponent* UBEGrabber::GetGrabbedComponent()
{
	UPrimitiveComponent* GrabbedComp = nullptr;
	// Only return valid.
	if (PhysicsHandleComp && PhysicsHandleComp->GetGrabbedComponent())
	{
		GrabbedComp = PhysicsHandleComp->GetGrabbedComponent();
	}
	return GrabbedComp;
}

void UBEGrabber::HandlePhysicsComp(float DeltaTime)
{
	if (GetGrabbedComponent())
	{
		GetGrabbedComponent()->SetWorldLocation(FMath::VInterpTo(
			GetGrabbedComponent()->GetComponentLocation(),
			GetLineTraceEnd(),
			DeltaTime,
			7.f)
		);
	}
}

bool UBEGrabber::TraceForHit(FHitResult& TheHit)
{
	bool bHit = false;
	TheHit = FHitResult();
	if (GetWorld())
	{
		GetWorld()->LineTraceSingleByObjectType(HitResult, PawnViewLoc, GetLineTraceEnd(), QueryParams, CollisionParams);
		// We hit something. Nice...
		if (HitResult.GetComponent())
		{
			bHit = true;
			TheHit = HitResult;
		}
	}
	return bHit;
}

