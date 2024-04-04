#include "FlockController.h"
#include "HAL/FileManager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

// Sets default values
AFlockController::AFlockController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFlockController::BeginPlay()
{
	Super::BeginPlay();

	// The file path relative to the project's Content directory
	FString FileName = TEXT("Data/20191117-S3F4676E1#1S20.txt");

	// Call LoadTrajectoryData with the path
	LoadTrajectoryData(FileName);

	// Filter trajectories based on a frame threshold
	FilterTrajectoriesByFrameThreshold(25); // Example threshold

	// Find the smallest common frame number
	SmallestCommonFrame = FindSmallestCommonFrame();
	CurrentFrame = SmallestCommonFrame;

	// Spawn bird actors
	SpawnBirdActors();
}

// Called every frame
void AFlockController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateBirdPositionsForFrame(CurrentFrame);
	CurrentFrame++;
}

void AFlockController::FilterTrajectoriesByFrameThreshold(int32 FrameThreshold)
{
	// Temporary map to hold filtered trajectories
	TMap<int32, TArray<FFramePosition>> FilteredTrajectories;

	// Iterate through all bird trajectories
	for (const auto &BirdTrajectoryPair : BirdTrajectories)
	{
		// If the number of frames for this bird exceeds the threshold
		if (BirdTrajectoryPair.Value.Num() > FrameThreshold)
		{
			// Add the whole trajectory to the filtered map
			FilteredTrajectories.Add(BirdTrajectoryPair.Key, BirdTrajectoryPair.Value);
		}
	}

	// Replace the original BirdTrajectories map with the filtered results
	BirdTrajectories = MoveTemp(FilteredTrajectories);

	// Optionally log the number of trajectories that met the criteria
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Filtered to %d trajectories meeting the frame threshold."), BirdTrajectories.Num()));
}

void AFlockController::LoadTrajectoryData(const FString &FileName)
{
	FString DataFilePath = FPaths::ProjectContentDir() + FileName;
	TArray<FString> Lines;

	if (FFileHelper::LoadFileToStringArray(Lines, *DataFilePath))
	{
		// Temporarily store positions for each BirdId as they're read
		TMap<int32, TArray<FFramePosition>> TempBirdTrajectories;

		for (FString &Line : Lines)
		{
			TArray<FString> Columns;
			Line.ParseIntoArray(Columns, TEXT(" "), true);

			if (Columns.Num() > 15)
			{
				int32 TrajectoryId = FCString::Atoi(*Columns[0]);
				int32 Frame = FCString::Atoi(*Columns[1]);
				FVector Position(FCString::Atof(*Columns[3]), FCString::Atof(*Columns[4]), FCString::Atof(*Columns[5]));
				FVector Velocity(FCString::Atof(*Columns[6]), FCString::Atof(*Columns[7]), FCString::Atof(*Columns[8]));
				UE_LOG(LogTemp, Warning, TEXT("Velocity: %s"), *Velocity.ToString());

				float WingRotation = FCString::Atof(*Columns[11]);

				// Add or append the position frame to the corresponding trajectory
				TempBirdTrajectories.FindOrAdd(TrajectoryId).Emplace(Frame, Position, Velocity, WingRotation);
			}
		}

		// Once all lines are processed, assign temp map to the class member
		BirdTrajectories = MoveTemp(TempBirdTrajectories);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Loaded %d trajectory frames."), BirdTrajectories.Num()));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to load trajectory data file: %s"), *DataFilePath);
	}
}

int32 AFlockController::FindSmallestCommonFrame()
{
	// Example logic to find the smallest frame number present in all trajectories.
	// This is a simplified approach and might need adjustment based on actual data structure and requirements.

	// Initialize with max int value to find the minimum
	int32 MinFrame = INT_MAX;

	for (const auto &Pair : BirdTrajectories)
	{
		if (Pair.Value.Num() > 0)
		{
			// Assuming trajectories are sorted by frame number
			int32 FirstFrameInTrajectory = Pair.Value[0].FrameNumber;
			if (FirstFrameInTrajectory < MinFrame)
			{
				MinFrame = FirstFrameInTrajectory;
			}
		}
	}

	return MinFrame == INT_MAX ? -1 : MinFrame; // Return -1 if no frame found
}

void AFlockController::UpdateBirdPositionsForFrame(int32 FrameNumber)
{
	for (ABirdActor *BirdActor : BirdActors)
	{
		if (BirdActor)
		{
			const TArray<FFramePosition> *Trajectory = BirdTrajectories.Find(BirdActor->GetBirdId());
			if (Trajectory)
			{
				const FFramePosition *FramePosition = Trajectory->FindByPredicate([FrameNumber](const FFramePosition &Item)
																				  { return Item.FrameNumber == FrameNumber; });

				if (FramePosition)
				{
					BirdActor->UpdatePosition(FramePosition->Position * 100.0f);
					BirdActor->SetWingRotationAngle(FramePosition->WingRotation * 50.0f);

					// Calculate the direction vector as the difference between velocity and position
					FVector Direction = -FramePosition->Velocity;

					// Normalize the direction vector to ensure it represents just the direction
					Direction = Direction.GetSafeNormal();

					if (!Direction.IsNearlyZero())
					{
						// Convert the direction vector into a rotation
						FRotator NewRotation = Direction.Rotation();

						// Set the bird actor's rotation to this new rotation
						BirdActor->SetActorRotation(NewRotation);
					}

					if (GEngine)
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Updated bird %d to position %s with rotation %s"), BirdActor->GetBirdId(), *FramePosition->Position.ToString(), *BirdActor->GetActorRotation().ToString()));
					}
				}
			}
		}
	}
}

void AFlockController::SpawnBirdActors()
{
	FVector Location(0.0f, 0.0f, 10.0f); // Starting location for the first bird
	FRotator Rotation(0.0f, 0.0f, 0.0f);

	// Iterate through all available trajectories to spawn birds
	for (const auto &TrajectoryPair : BirdTrajectories)
	{
		int32 BirdId = TrajectoryPair.Key; // The bird's unique ID from the trajectory map
		ABirdActor *NewBird = GetWorld()->SpawnActor<ABirdActor>(ABirdActor::StaticClass(), Location, Rotation);

		if (NewBird)
		{
			NewBird->SetBirdId(BirdId); // Assign the bird's ID
			UE_LOG(LogTemp, Warning, TEXT("Spawned bird actor with ID: %d"), BirdId);
			BirdActors.Add(NewBird); // Add the bird actor to the list of managed bird actors

			// Update Location for the next bird to avoid overlap
			Location.X += 120.0f;
		}
	}
}