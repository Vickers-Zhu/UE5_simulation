// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BirdSpawnTest.generated.h"

UCLASS()
class FLOCKSIMULATION_API ABirdSpawnTest : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABirdSpawnTest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Mesh component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent *MeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Materials")
	UMaterialInstanceDynamic *MaterialInstanceDynamic;
};
