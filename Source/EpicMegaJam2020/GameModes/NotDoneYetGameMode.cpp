#include "NotDoneYetGameMode.h"
#include "EpicMegaJam2020/Characters/EnemyCharacter.h"
#include "EpicMegaJam2020/Characters/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

ANotDoneYetGameMode::ANotDoneYetGameMode() 
{
    PlayerCharacter = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void ANotDoneYetGameMode::BeginPlay() 
{
    GameOver = false;    
}

void ANotDoneYetGameMode::ActorDied(AActor* DeadActor) 
{
    if (DeadActor == PlayerCharacter) 
    {
        UE_LOG(LogTemp, Warning, TEXT("Player Died!"));
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
    	UE_LOG(LogTemp, Warning, TEXT("GameMode: ActorDamaged!"));
        UpdatePlayerHP(Player->GetHealth());
    }
}