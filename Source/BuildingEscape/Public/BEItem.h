// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BEItem.generated.h"

UCLASS()
class BUILDINGESCAPE_API ABEItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABEItem();

protected:
	
// 	UPROPERTY(EditAnywhere, BlueprintReadWrite)
// 	bool bIsGrabbable;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USceneComponent* SceneComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	
	// Setter for the Static Mesh Component.
	UFUNCTION(BlueprintCallable)
	void SetStaticMesh(UStaticMeshComponent* NewStaticMesh);

	// Getter for the Static Mesh Component.
	UFUNCTION(BlueprintCallable, BlueprintPure)
	UStaticMeshComponent* GetStaticMesh();

// 	UFUNCTION(BlueprintCallable)
// 	void SetIsGrabbable(bool bGrabbable);
// 
// 	UFUNCTION(BlueprintCallable, BlueprintPure)
// 	bool GetIsGrabbable();

};
