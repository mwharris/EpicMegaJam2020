#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"

void AEnemyAIController::BeginPlay() 
{
    Super::BeginPlay();
    PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

void AEnemyAIController::OnPossess(APawn* InPawn) 
{
    if (PlayerActor != nullptr) 
    {
        MoveToActor(PlayerActor);
    }    
}