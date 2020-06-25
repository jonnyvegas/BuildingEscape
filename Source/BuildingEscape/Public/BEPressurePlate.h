// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BEPressurePlate.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FItemsWeightChangedDel, float , NewWeight);

class ABEItem;
UCLASS()
class BUILDINGESCAPE_API ABEPressurePlate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABEPressurePlate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Want to have something that we can move relatively to.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USceneComponent* SceneComp;

	// Need to overlap with items here.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxCollisionComp;

	// Placed above collision to highlight the area for the player.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USpotLightComponent* SpotLightComp;

	UPROPERTY()
	TArray<ABEItem*> BEItemArray;

	

public:	
	


	/**
	* Binds to the overlap on the Box Collision.
	*/
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	/**
	 * Bind to ending overlap. Send an event trigger when this happens.
	 */
	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void AddItemToArray(ABEItem* ItemToAdd);

	UFUNCTION()
	float GetItemsWeight();

	UFUNCTION()
	ABEItem* CheckIfBEItem(AActor* ActorToCheck);//, ABEItem* &BEItem);

	FItemsWeightChangedDel ItemsWeightChangedDel;
};
