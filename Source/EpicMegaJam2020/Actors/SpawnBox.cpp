#include "SpawnBox.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "EpicMegaJam2020/GameModes/NotDoneYetGameMode.h"
#include "EpicMegaJam2020/Characters/EnemyCharacter.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

ASpawnBox::ASpawnBox()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	SetRootComponent(SceneComponent);

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawn Volume"));
	BoxCollider->SetupAttachment(RootComponent);
}

void ASpawnBox::BeginPlay()
{
	Super::BeginPlay();
	// Get a reference to the player for movement purposes
	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (PlayerPawn != nullptr) 
    {
        PlayerOffset = GetActorLocation() - PlayerPawn->GetActorLocation();
    }
	// Get a reference to the GameMode and register with it
	GameModeRef = Cast<ANotDoneYetGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameModeRef != nullptr) 
	{
		// GameModeRef->SetSpawnBox(this);
		GameModeRef->AddSpawnBox(this);
	}
}

void ASpawnBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Update our position as the player moves
	if (PlayerPawn && PlayerOffset != FVector::ZeroVector) 
	{
		FVector NewLocation = PlayerPawn->GetActorLocation() + PlayerOffset;
		SetActorLocation(NewLocation);
	}
}

void ASpawnBox::SpawnEnemies(int32 NumEnemies) 
{
	for (size_t i = 0; i < NumEnemies; i++)
	{
		FVector Location = UKismetMathLibrary::RandomPointInBoundingBox(
			SceneComponent->GetComponentLocation(), 
			BoxCollider->GetScaledBoxExtent()
		);
		FActorSpawnParameters SpawnParams;
		GetWorld()->SpawnActor<AEnemyCharacter>(EnemyClass, Location, FRotator::ZeroRotator, SpawnParams);
	}
}