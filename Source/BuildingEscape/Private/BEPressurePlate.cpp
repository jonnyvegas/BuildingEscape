// Fill out your copyright notice in the Description page of Project Settings.


#include "BEPressurePlate.h"
#include "Components/BoxComponent.h"
#include "../Public/BEItem.h"
#include "Components/SpotLightComponent.h"

// Sets default values
ABEPressurePlate::ABEPressurePlate()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	RootComponent = SceneComp;

	BoxCollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollisionComp"));
	BoxCollisionComp->SetupAttachment(RootComponent);
	BoxCollisionComp->SetBoxExtent(FVector(64.f));
	BoxCollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ABEPressurePlate::BeginOverlap);
	BoxCollisionComp->OnComponentEndOverlap.AddDynamic(this, &ABEPressurePlate::EndOverlap);

	SpotLightComp = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLightComp"));
	SpotLightComp->SetupAttachment(RootComponent);
	SpotLightComp->SetRelativeRotation(FRotator(270.f, 0.f, 0.f));
	SpotLightComp->SetRelativeLocation(FVector(0.f, 0.f, 125.f));
	BEItemArray = {};
	
}

// Called when the game starts or when spawned
void ABEPressurePlate::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void ABEPressurePlate::BeginOverlap(UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABEItem* BEItem = CheckIfBEItem(OtherActor);//, BEItem);
	if (BEItem)
	{
		// Activate physics if not done.
		if (BEItem->GetStaticMesh() && !BEItem->GetStaticMesh()->IsSimulatingPhysics())
		{
			BEItem->GetStaticMesh()->SetSimulatePhysics(true);
		}
		// Add to array.
		BEItemArray.AddUnique(BEItem);
		// Check weight.
		ItemsWeightChangedDel.Broadcast(GetItemsWeight());
// 		if (GetItemsWeight() >= 200.f)
// 		{
// 			// Potentially open door.
// 			OpenOrCloseDoorDel.Broadcast(true);
// 		}
	}
 }

void ABEPressurePlate::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Remove item from array.
	ABEItem* BEItem = CheckIfBEItem(OtherActor);
	if (BEItem)
	{
		BEItemArray.Remove(BEItem);
	}
	// Check weight.
	ItemsWeightChangedDel.Broadcast(GetItemsWeight());
	// Close door (probably).
}

void ABEPressurePlate::AddItemToArray(ABEItem* ItemToAdd)
{
	if (!BEItemArray.Contains(ItemToAdd))
	{
		BEItemArray.AddUnique(ItemToAdd);
	}
}

float ABEPressurePlate::GetItemsWeight()
{
	float TotalWeight = 0;
	for (ABEItem* BEItem : BEItemArray)
	{
		TotalWeight += BEItem->GetStaticMesh()->GetMass();
	}
	return TotalWeight;
}

ABEItem* ABEPressurePlate::CheckIfBEItem(AActor* ActorToCheck)//, ABEItem* &BEItem)
{
	ABEItem* BEItem = Cast<ABEItem>(ActorToCheck);
	return BEItem;// != nullptr;
}

