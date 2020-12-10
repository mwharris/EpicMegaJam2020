#include "MissionPoint.h"
#include "Components/BoxComponent.h"
#include "EpicMegaJam2020/Characters/PlayerCharacter.h"
#include "EpicMegaJam2020/GameModes/NotDoneYetGameMode.h"
#include "Kismet/GameplayStatics.h"

AMissionPoint::AMissionPoint()
{
	PrimaryActorTick.bCanEverTick = false;
	Triggered = false;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	SetRootComponent(BoxCollider);
}

void AMissionPoint::BeginPlay()
{
	Super::BeginPlay();
    // Get a reference to our player and game mode
	Player = Cast<AActor>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	GameModeRef = Cast<ANotDoneYetGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	// Hook into the component overlap event
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AMissionPoint::OnBeginOverlap);
}

void AMissionPoint::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	if (Triggered || OtherActor == nullptr || Player == nullptr || OtherActor != Player ) 
	{
		return;
	}
	Triggered = true;
	if (FinalMission) 
	{
		GameModeRef->PlayerWon();
	}
	else 
	{
		GameModeRef->ShowStoryDialogue(CharacterName, DialogueText);
	}
}