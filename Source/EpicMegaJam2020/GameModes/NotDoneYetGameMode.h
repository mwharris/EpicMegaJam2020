#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NotDoneYetGameMode.generated.h"

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
	bool GameOver;
	class APlayerCharacter* PlayerCharacter;
	
};
