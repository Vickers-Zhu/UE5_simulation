// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// #include "NiagaraComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BirdActor.generated.h"

UCLASS()
class FLOCKSIMULATIONS_API ABirdActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABirdActor();

	// Sets the bird's unique ID
	void SetBirdId(int32 NewId);

	// Retrieves the bird's unique ID
	int32 GetBirdId() const;
	// Function to update the bird's position
	void UpdatePosition(const FVector &NewPosition);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Unique identifier for the bird
	int32 BirdId;

	// Mesh component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent *MeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Materials")
	UMaterialInstanceDynamic *DynamicMaterial;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetWingRotationAngle(float Angle);
};
