// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BirdActor.h"
#include "FlockController.generated.h"

class ABirdActor;

USTRUCT(BlueprintType)
struct FFramePosition
{
	GENERATED_BODY()

public:
	// Frame number
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 FrameNumber;

	// Position vector for this frame
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector Position;

	FFramePosition() : FrameNumber(0), Position(FVector::ZeroVector) {}

	FFramePosition(int32 InFrameNumber, FVector InPosition)
		: FrameNumber(InFrameNumber), Position(InPosition) {}
};

UCLASS()
class FLOCKSIMULATION_API AFlockController : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFlockController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Function to load trajectory data
	UFUNCTION(BlueprintCallable, Category = "Trajectory")
	void LoadTrajectoryData(const FString &FileName);

	UFUNCTION(BlueprintCallable, Category = "Trajectory")
	void FilterTrajectoriesByFrameThreshold(int32 FrameThreshold);

	UFUNCTION(BlueprintCallable, Category = "Trajectory")
	int32 FindSmallestCommonFrame();

	UFUNCTION(BlueprintCallable, Category = "Birds")
	void UpdateBirdPositionsForFrame(int32 FrameNumber);

	// Function to spawn bird actors
	UFUNCTION(BlueprintCallable, Category = "Birds")
	void SpawnBirdActors();

private:
	// Map to hold trajectories, keyed by BirdId
	TMap<int32, TArray<FFramePosition>> BirdTrajectories;

	// Current simulation frame
	int32 CurrentFrame = 0;

	// Array to keep track of bird actors
	TArray<ABirdActor *> BirdActors;

	// Smallest common frame number across all trajectories
	int32 SmallestCommonFrame = -1;
};
