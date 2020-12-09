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
    if (SpawnBox != nullptr && !GameOver) 
    {
        SpawnBox->SpawnEnemies(RandomSpawnAmount());
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

void ANotDoneYetGameMode::ActorDied(AActor* DeadActor) 
{
    if (DeadActor == PlayerCharacter) 
    {
        GameOver = true;
        GetWorldTimerManager().ClearTimer(SpawnTimer);
        UpdatePlayerHP(PlayerCharacter->GetHealth());
        PlayerCharacter->HandleDeath();
    }
    else if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(DeadActor)) 
    {
        Enemy->HandleDeath();
    }
}

void ANotDoneYetGameMode::ActorDamaged(AActor* DamagedActor) 
{
    if (APlayerCharacter* Player = Cast<APlayerCharacter>(DamagedActor)) 
    {
        UpdatePlayerHP(Player->GetHealth());
    }
}

void ANotDoneYetGameMode::SetSpawnBox(ASpawnBox* NewSpawnBox) 
{
    SpawnBox = NewSpawnBox;
}