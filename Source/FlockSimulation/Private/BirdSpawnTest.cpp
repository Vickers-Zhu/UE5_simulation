// Fill out your copyright notice in the Description page of Project Settings.

#include "BirdSpawnTest.h"

// Sets default values
ABirdSpawnTest::ABirdSpawnTest()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

	// Assuming you have a mesh and a material instance in your project
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Mesh(TEXT("/Game/BeefyBlackbirds/Meshes/Blackbirds/BrewersBlackbird/Mesh_BrewersBlackbird.Mesh_BrewersBlackbird"));
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> MaterialInstance(TEXT("/Game/BeefyBlackbirds/Meshes/Blackbirds/BrewersBlackbird/MI_BrewersBlackbird_Particle.MI_BrewersBlackbird_Particle"));

	if (Mesh.Succeeded())
	{
		MeshComponent->SetStaticMesh(Mesh.Object);
		MeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	}

	if (MaterialInstance.Succeeded())
	{
		MaterialInstanceDynamic = UMaterialInstanceDynamic::Create(MaterialInstance.Object, MeshComponent);
		MeshComponent->SetMaterial(0, MaterialInstanceDynamic);
	}
}

// Called when the game starts or when spawned
void ABirdSpawnTest::BeginPlay()
{
	Super::BeginPlay();
	MaterialInstanceDynamic->SetScalarParameterValue(FName("Wing Anim Speed"), 2.0f);
}

// Called every frame
void ABirdSpawnTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
