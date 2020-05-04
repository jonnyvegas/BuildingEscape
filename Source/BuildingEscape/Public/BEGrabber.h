// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CollisionQueryParams.h"
#include "BEGrabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UBEGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBEGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void GrabItem();

	UFUNCTION()
	void ReleaseItem();

	UFUNCTION()
	FVector GetLineTraceEnd();

	UFUNCTION()
	UPrimitiveComponent* GetGrabbedComponent();

	UFUNCTION()
	void HandlePhysicsComp(float DeltaTime);

	UFUNCTION()
	bool TraceForHit(FHitResult& TheHit);

protected:

	UPROPERTY()
	class UPhysicsHandleComponent* PhysicsHandleComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UPhysicsHandleComponent> PhysicsHandleClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UPrimitiveComponent> PrimitiveCompClass;

	UPROPERTY()
	FVector PawnViewLoc;

	UPROPERTY()
	FRotator PawnViewRot;

	UPROPERTY()
	FVector ViewRotToVector;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float TraceDistance;

	ETraceTypeQuery TracingType;

	UPROPERTY()
	TArray<AActor*> ActorsToIgnore;

	UPROPERTY()
	FHitResult HitResult;
		
	UPROPERTY()
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;

	//UPROPERTY()
	FCollisionObjectQueryParams QueryParams;

	//UPROPERTY()
	FCollisionQueryParams CollisionParams;

	UPROPERTY()
	class ABEPawnNew* BEPawn;

	
};
