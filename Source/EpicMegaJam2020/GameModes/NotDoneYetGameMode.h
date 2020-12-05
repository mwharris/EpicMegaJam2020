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

private:
	bool GameOver;
	
};
