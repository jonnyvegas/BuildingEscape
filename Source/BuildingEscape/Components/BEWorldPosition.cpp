// Fill out your copyright notice in the Description page of Project Settings.


#include "BEWorldPosition.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UBEWorldPosition::UBEWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBEWorldPosition::BeginPlay()
{
	Super::BeginPlay();

// 	FString Log = TEXT("Some text");
// 	FString* PtrLog = &Log;
// 	// ...
// 	UE_LOG(LogTemp, Warning, TEXT("%s"), *Log);
	if (GetOwner())
	{
		FString OwnerName = GetOwner()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("Owner's name: %s"), *OwnerName);
		FString ObjectPosition = GetOwner()->GetActorTransform().GetLocation().ToCompactString();
		UE_LOG(LogTemp, Warning, TEXT("Object position: %s"), *ObjectPosition);
	}
}


// Called every frame
void UBEWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

