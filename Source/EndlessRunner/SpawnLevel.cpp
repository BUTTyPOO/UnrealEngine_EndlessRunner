// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnLevel.h"

#include "BaseLevel.h"
#include "Engine.h"
#include "Components/BoxComponent.h"

// Sets default values
ASpawnLevel::ASpawnLevel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnLevel::BeginPlay()
{
	Super::BeginPlay();
    SpawnLevel(true);
    SpawnLevel(false);
    SpawnLevel(false);
}

// Called every frame
void ASpawnLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnLevel::SpawnLevel(bool IsFirst)
{
	SpawnLocation = FVector(0.f, 1000.f, 0.f);
	SpawnRotation = FRotator(0, 90, 0);

	if (!IsFirst)
	{
		ABaseLevel* LastLevel = LevelList.Last();
		SpawnLocation = LastLevel->GetSpawnLocation()->GetComponentTransform().GetTranslation();
	}

	RandomLevel = FMath::RandRange(1, 10);
	ABaseLevel* NewLevel = nullptr;
	TSubclassOf<ABaseLevel> LevelToSpawn;
	if (RandomLevel == 1)
	{
		LevelToSpawn = Level1;
	}
    else if (RandomLevel == 2)
    {
        LevelToSpawn = Level2;
    }
    else if (RandomLevel == 3)
    {
        LevelToSpawn = Level3;
    }
    else if (RandomLevel == 4)
    {
        LevelToSpawn = Level4;
    }
    else if (RandomLevel == 5)
    {
        LevelToSpawn = Level5;
    }
    else
    {
        LevelToSpawn = Level6;
    }

    NewLevel = GetWorld()->SpawnActor<ABaseLevel>(LevelToSpawn, SpawnLocation, SpawnRotation, SpawnInfo);

    if (NewLevel)
    {
        if (NewLevel->GetTrigger())
        {
            NewLevel->GetTrigger()->OnComponentBeginOverlap.AddDynamic(this, &ASpawnLevel::OnOverlapBegin);
        }
    }
    LevelList.Add(NewLevel);
    if (LevelList.Num() > 5)
    {
        LevelList.RemoveAt(0);
    }
}

void ASpawnLevel::OnOverlapBegin(UPrimitiveComponent* OverLappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    SpawnLevel(false);
}

