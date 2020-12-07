#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnBox.generated.h"

class AEnemyCharacter;
class ANotDoneYetGameMode;
class UBoxComponent;
class USceneComponent;

UCLASS()
class EPICMEGAJAM2020_API ASpawnBox : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawnBox();
	virtual void Tick(float DeltaTime) override;
	void SpawnEnemies(int32 NumEnemies);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Spawning", meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Spawning", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxCollider;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Spawning", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AEnemyCharacter> EnemyClass;

	APawn* PlayerPawn;
	FVector PlayerOffset;
	ANotDoneYetGameMode* GameModeRef;

};