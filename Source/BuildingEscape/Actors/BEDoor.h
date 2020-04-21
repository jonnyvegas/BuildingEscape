// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BEDoor.generated.h"

UCLASS()
class BUILDINGESCAPE_API ABEDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABEDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION(BlueprintCallable)
	void OpenOrCloseDoor(float DeltaTime, bool bOpen = true);

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class USceneComponent* SceneComp;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	class UStaticMeshComponent* DoorMeshComp;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	UStaticMeshComponent* DoorFrameComp;

	UPROPERTY(EditAnywhere)
	class ATriggerVolume* PressurePlate;

// 	UPROPERTY(EditAnywhere)
// 	class AActor* ActorToOpenDoor;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FRotator DoorRotation;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float DoorRotationRate;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	float YawToAdd;

	UPROPERTY()
	float TargetYaw;

	UPROPERTY()
	float CurrentYaw;

	UPROPERTY()
	float InitialYaw;

	UPROPERTY()
	float DoorLastOpened;

	UPROPERTY()
	float DoorDelay;

	UPROPERTY()
	TArray<AActor*> OverlappingActors;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ActorSubclass;

	UPROPERTY()
	APawn* PawnToCheck;

};
