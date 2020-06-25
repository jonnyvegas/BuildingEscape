// Fill out your copyright notice in the Description page of Project Settings.


#include "BEItem.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABEItem::ABEItem()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create components/set as root.
	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	RootComponent = SceneComp;
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComp");
	StaticMeshComp->SetupAttachment(RootComponent);
	
	// Setup Collision.
	StaticMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMeshComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	StaticMeshComp->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Block);
	StaticMeshComp->SetSimulatePhysics(true);
	StaticMeshComp->SetCollisionObjectType(ECC_PhysicsBody);
	StaticMeshComp->SetMassOverrideInKg(NAME_None, 100.f);
}

// Called when the game starts or when spawned
void ABEItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABEItem::SetStaticMesh(UStaticMeshComponent* NewStaticMesh)
{
	if (NewStaticMesh)
	{
		StaticMeshComp = NewStaticMesh;
	}
}

UStaticMeshComponent* ABEItem::GetStaticMesh()
{
	return StaticMeshComp;
}

// bool ABEItem::GetIsGrabbable()
// {
// 	return bIsGrabbable;
// }
// 
// void ABEItem::SetIsGrabbable(bool bGrabbable)
// {
// 	bIsGrabbable = bGrabbable;
// }
