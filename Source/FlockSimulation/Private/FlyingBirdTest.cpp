// Fill out your copyright notice in the Description page of Project Settings.

#include "FlyingBirdTest.h"

// Sets default values
AFlyingBirdTest::AFlyingBirdTest()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Initialize the visual component and attach it to the actor's root component
	VisualComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	RootComponent = VisualComponent;

	// Set a default static mesh (replace with any mesh you want to use)
	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (CubeVisualAsset.Succeeded())
	{
		VisualComponent->SetStaticMesh(CubeVisualAsset.Object);
		VisualComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}

	// Set default velocity
	Velocity = FVector(100.0f, 0.0f, 0.0f); // Example velocity
}

// Called when the game starts or when spawned
void AFlyingBirdTest::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFlyingBirdTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Update the movement
	UpdateMovement(DeltaTime);
}

void AFlyingBirdTest::UpdateMovement(float DeltaTime)
{
	// Move the actor by the velocity vector scaled by DeltaTime
	FVector NewLocation = GetActorLocation() + (Velocity * DeltaTime);
	SetActorLocation(NewLocation);
}
