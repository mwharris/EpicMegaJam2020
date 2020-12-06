#include "HealthComponent.h"
#include "EpicMegaJam2020/GameModes/NotDoneYetGameMode.h"
#include "Kismet/GameplayStatics.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	// Intialize our starting HP
	Health = MaxHealth;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	// Cache a reference to our GameMode
	GameModeRef = Cast<ANotDoneYetGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	// Bind our TakeDamage function to the OnTakeAnyDamage event
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser) 
{
	if (Damage <= 0 || Health <= 0) 
	{
		return;
	}
	// Decrease our HP
	Health -= Damage;
	// Tell the GameMode that we died
	if (Health <= 0) 
	{
		GameModeRef->ActorDied(GetOwner());
	}
	else
	{
		GameModeRef->ActorDamaged(DamagedActor);
	}
}

bool UHealthComponent::IsDead() const
{
	return Health <= 0;	
}

float UHealthComponent::GetHealth() const
{
	return Health;
}