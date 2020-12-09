#include "NotDoneYetGameMode.h"
#include "Engine/World.h"
#include "EpicMegaJam2020/Characters/EnemyCharacter.h"
#include "EpicMegaJam2020/Characters/PlayerCharacter.h"
#include "EpicMegaJam2020/Actors/SpawnBox.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

ANotDoneYetGameMode::ANotDoneYetGameMode() 
{

}

void ANotDoneYetGameMode::BeginPlay() 
{
    GameOver = false;
    PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    if (PlayerCharacter == nullptr) 
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to find PlayerCharacter!"));
    }
    GetWorldTimerManager().SetTimer(SpawnTimer, this, &ANotDoneYetGameMode::SpawnEnemy, SpawnTime, true);
}

void ANotDoneYetGameMode::SpawnEnemy() 
{
    if (SpawnBoxes.Num() > 0 && !GameOver) 
    {
        int32 Index = RandomSpawnBox();
        int32 NumSpawns = RandomSpawnAmount();
        while (NumSpawns > 0) 
        {
            if (Index >= SpawnBoxes.Num()) 
            {
                Index = 0;
            }
            ASpawnBox* PossibleBox = SpawnBoxes[Index];
            if (PossibleBox != nullptr)
            {
                PossibleBox->SpawnEnemies(1);
            }
            Index++;
            NumSpawns--;
        }
    }
}

// Pick a random number of enemies to spawn between our min and max
int32 ANotDoneYetGameMode::RandomSpawnAmount() const
{
    int32 SpawnAmount = SpawnAmountMin;
    if (SpawnAmountMin != SpawnAmountMax) 
    {
        SpawnAmount = FMath::RandRange(SpawnAmountMin, SpawnAmountMax);
    }
    return SpawnAmount;    
}

int32 ANotDoneYetGameMode::RandomSpawnBox() const
{
    int32 SpawnIndex = 0;
    if (SpawnBoxes.Num() > 0) 
    {
        SpawnIndex = FMath::RandRange(0, SpawnBoxes.Num() - 1);
    }
    return SpawnIndex;
}

void ANotDoneYetGameMode::ActorDied(AActor* DeadActor) 
{
    if (DeadActor == PlayerCharacter) 
    {
        GameOver = true;
        GetWorldTimerManager().ClearTimer(SpawnTimer);
		UGameplayStatics::SpawnSound2D(GetWorld(), PlayerDeathSound);
        UpdatePlayerHP(PlayerCharacter->GetHealth());
        PlayerCharacter->HandleDeath();
    }
    else if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(DeadActor)) 
    {
		UGameplayStatics::SpawnSound2D(GetWorld(), ZombieDeathSound);
        Enemy->HandleDeath();
    }
}

void ANotDoneYetGameMode::ActorDamaged(AActor* DamagedActor) 
{
    if (APlayerCharacter* Player = Cast<APlayerCharacter>(DamagedActor)) 
    {
		UGameplayStatics::SpawnSound2D(GetWorld(), PlayerHurtSound);
        UpdatePlayerHP(Player->GetHealth());
    }
    else 
    {
		UGameplayStatics::SpawnSound2D(GetWorld(), ZombieHurtSound);
    }
}

void ANotDoneYetGameMode::SetSpawnBox(ASpawnBox* NewSpawnBox) 
{
    // SpawnBox = NewSpawnBox;
}

void ANotDoneYetGameMode::AddSpawnBox(ASpawnBox* NewSpawnBox) 
{
    SpawnBoxes.Add(NewSpawnBox);
}