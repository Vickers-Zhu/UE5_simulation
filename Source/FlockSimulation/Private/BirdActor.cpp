// Fill out your copyright notice in the Description page of Project Settings.

#include "BirdActor.h"

// Sets default values
ABirdActor::ABirdActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Create and set up the visual component as the root component
	SphereComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	// SphereComponent->SetWorldScale3D(FVector(0.1f, 0.1f, 0.1f));
	RootComponent = SphereComponent;

	// Set the static mesh to the basic sphere
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	if (SphereVisualAsset.Succeeded())
	{
		SphereComponent->SetStaticMesh(SphereVisualAsset.Object);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not find the Sphere mesh!"));
	}

	// // Initialize the Niagara component
	// TrailEffect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("TrailEffect"));
	// TrailEffect->SetupAttachment(RootComponent);

	// // Load and set the Niagara system for the trail effect
	// static ConstructorHelpers::FObjectFinder<UNiagaraSystem> TrailSystem(TEXT("/Game/FX/Trail_beam.uasset"));
	// if (TrailSystem.Succeeded())
	// {
	// 	TrailEffect->SetAsset(TrailSystem.Object);
	// }

	// // You can start with the effect disabled and enable it when needed
	// TrailEffect->SetAutoActivate(false);
}

// Called when the game starts or when spawned
void ABirdActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABirdActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABirdActor::UpdatePosition(const FVector &NewPosition)
{
	SetActorLocation(NewPosition);
}

void ABirdActor::SetBirdId(int32 NewId)
{
	BirdId = NewId;
}

int32 ABirdActor::GetBirdId() const
{
	return BirdId;
}