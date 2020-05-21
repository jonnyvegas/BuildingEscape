// Fill out your copyright notice in the Description page of Project Settings.


#include "BEPressurePlate.h"
#include "Components/BoxComponent.h"

// Sets default values
ABEPressurePlate::ABEPressurePlate()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxCollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollisionComp"));
	BoxCollisionComp->SetupAttachment(RootComponent);
	BoxCollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ABEPressurePlate::BeginOverlap);
	
}

// Called when the game starts or when spawned
void ABEPressurePlate::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABEPressurePlate::BeginOverlap(UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UStaticMeshComponent* StaticMeshComp = Cast<UStaticMeshComponent>(OtherComp);
	if (StaticMeshComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("static mesh comp - valid"));
	}
// 	else
// 	{
// 		UE_LOG(LogTemp, Warning, TEXT("static mesh comp - NOT valid"));
// 	}
 }

