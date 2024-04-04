// Fill out your copyright notice in the Description page of Project Settings.

#include "BirdActor.h"

// Sets default values
ABirdActor::ABirdActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

	// Assuming you have a mesh and a material instance in your project
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Game/BeefyBlackbirds/Meshes/Cowbirds/BrownHeadedCowbird/Mesh_BrownHeadedCowbird.Mesh_BrownHeadedCowbird"));
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> MaterialInstance(TEXT("/Game/BeefyBlackbirds/Meshes/Cowbirds/BrownHeadedCowbird/MI_BrownHeadedCowbird_Particle.MI_BrownHeadedCowbird_Particle"));
	{
		MeshComponent->SetStaticMesh(Mesh.Object);
		MeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}

	if (MaterialInstance.Succeeded())
	{
		MeshComponent->SetMaterial(0, MaterialInstance.Object);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Could not find the Sphere mesh!"));
	}
	FVector NewScale(3.0f, 3.0f, 3.0f); // Example scale, adjust as needed
	SetActorScale3D(NewScale);
}

// Called when the game starts or when spawned
void ABirdActor::BeginPlay()
{
	Super::BeginPlay();

	UMaterialInterface *Material = MeshComponent->GetMaterial(0);
	DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);
	MeshComponent->SetMaterial(0, DynamicMaterial);
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

void ABirdActor::SetWingRotationAngle(float Angle)
{
	if (DynamicMaterial)
	{
		DynamicMaterial->SetScalarParameterValue(FName("Wing Rotation Angle"), Angle);
	}
}