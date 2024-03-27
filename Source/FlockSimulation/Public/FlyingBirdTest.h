// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlyingBirdTest.generated.h"

UCLASS()
class FLOCKSIMULATION_API AFlyingBirdTest : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFlyingBirdTest();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Properties
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent *VisualComponent;

	// Velocity of the bird
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FVector Velocity;

	// Update the flying object's position
	void UpdateMovement(float DeltaTime);
};
