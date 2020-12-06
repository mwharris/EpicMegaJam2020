#include "NotDoneYetGameMode.h"
#include "Engine/World.h"
#include "Engine/TargetPoint.h"
#include "EpicMegaJam2020/Characters/EnemyCharacter.h"
#include "EpicMegaJam2020/Characters/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

ANotDoneYetGameMode::ANotDoneYetGameMode() 
{
    PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void ANotDoneYetGameMode::BeginPlay() 
{
    GameOver = false;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), SpawnPoints);
    GetWorldTimerManager().SetTimer(SpawnTimer, this, &ANotDoneYetGameMode::SpawnEnemy, SpawnTime, true);
}

void ANotDoneYetGameMode::SpawnEnemy() 
{
    if (SpawnPoints.Num() > 0) 
    {
        int32 SpawnAmount = RandomSpawnAmount();
        UE_LOG(LogTemp, Warning, TEXT("Spawning %f enemies"), SpawnAmount);
        for (size_t i = 0; i < SpawnAmount; i++)
        {
            // Pick a random spawn point and spawn an enemy there
            AActor* SpawnPoint = SpawnPoints[RandomSpawnIndex()];
            FActorSpawnParameters SpawnParams;
            GetWorld()->SpawnActor<AEnemyCharacter>(EnemyClass, SpawnPoint->GetActorLocation(), FRotator::ZeroRotator, SpawnParams);
        }
    }
}

// Pick a random spawn point to spawn at
int32 ANotDoneYetGameMode::RandomSpawnIndex() const
{
    int32 Index = 0;
    if (SpawnPoints.Num() > 1) 
    {
        Index = FMath::RandRange(0, SpawnPoints.Num() - 1);
    }
    return Index;
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