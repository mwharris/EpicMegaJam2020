#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NotDoneYetGameMode.generated.h"

class AEnemyCharacter;

UCLASS()
class EPICMEGAJAM2020_API ANotDoneYetGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ANotDoneYetGameMode();
	void ActorDied(AActor* DeadActor);
	void ActorDamaged(AActor* DamagedActor);

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdatePlayerHP(float NewHP);

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Spawning", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AEnemyCharacter> EnemyClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Spawning", meta = (AllowPrivateAccess = "true"))
	float SpawnTime = 5.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Spawning", meta = (AllowPrivateAccess = "true"))
	int32 SpawnAmountMin = 1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Spawning", meta = (AllowPrivateAccess = "true"))
	int32 SpawnAmountMax = 2;

	bool GameOver;
	class APlayerCharacter* PlayerCharacter;
	FTimerHandle SpawnTimer;
	TArray<AActor*> SpawnPoints;

	void SpawnEnemy();
	int32 RandomSpawnIndex() const;
	int32 RandomSpawnAmount() const;
	
};
