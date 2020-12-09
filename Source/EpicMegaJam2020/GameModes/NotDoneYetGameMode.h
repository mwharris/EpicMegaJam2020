#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NotDoneYetGameMode.generated.h"

class AEnemyCharacter;
class ASpawnBox;

UCLASS()
class EPICMEGAJAM2020_API ANotDoneYetGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ANotDoneYetGameMode();
	void ActorDied(AActor* DeadActor);
	void ActorDamaged(AActor* DamagedActor);
	void SetSpawnBox(ASpawnBox* NewSpawnBox);
	void AddSpawnBox(ASpawnBox* NewSpawnBox);

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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Lifetime", meta = (AllowPrivateAccess = "true"))
	bool GameOver;
	UPROPERTY(EditAnywhere, Category = "Sounds")
	USoundBase* PlayerHurtSound;
	UPROPERTY(EditAnywhere, Category = "Sounds")
	USoundBase* PlayerDeathSound;
	UPROPERTY(EditAnywhere, Category = "Sounds")
	USoundBase* ZombieHurtSound;
	UPROPERTY(EditAnywhere, Category = "Sounds")
	USoundBase* ZombieDeathSound;

	class APlayerCharacter* PlayerCharacter;
	FTimerHandle SpawnTimer;
	TArray<ASpawnBox*> SpawnBoxes;

	void SpawnEnemy();
	int32 RandomSpawnAmount() const;
	int32 RandomSpawnBox() const;
	
};
