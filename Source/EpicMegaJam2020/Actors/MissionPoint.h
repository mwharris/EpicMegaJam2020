#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MissionPoint.generated.h"

class UBoxComponent;
class ANotDoneYetGameMode;
class APlayerCharacter;

UCLASS()
class EPICMEGAJAM2020_API AMissionPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	AMissionPoint();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category="Components")
	UBoxComponent* BoxCollider = nullptr;
	UPROPERTY(EditAnywhere, Category="Mission")
	FString CharacterName;
	UPROPERTY(EditAnywhere, Category="Mission")
	FString DialogueText;
	UPROPERTY(EditAnywhere, Category="Mission")
	bool FinalMission;

	bool Triggered = false;
	ANotDoneYetGameMode* GameModeRef;
	AActor* Player;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};