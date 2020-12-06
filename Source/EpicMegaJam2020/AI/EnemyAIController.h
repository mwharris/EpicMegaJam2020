#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

UCLASS()
class EPICMEGAJAM2020_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	// virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

private:
	class AActor* PlayerActor;
	
};
