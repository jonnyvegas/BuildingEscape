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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsGrabbable;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* StaticMeshComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	
	UFUNCTION(BlueprintCallable)
	void SetStaticMesh(UStaticMeshComponent* NewStaticMesh);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UStaticMeshComponent* GetStaticMesh();

	UFUNCTION(BlueprintCallable)
	void SetIsGrabbable(bool bGrabbable);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool GetIsGrabbable();

};
