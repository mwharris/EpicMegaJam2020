#include "BaseCharacter.h"
#include "EpicMegaJam2020/Components/HealthComponent.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ABaseCharacter::HandleDeath() 
{

}

float ABaseCharacter::GetHealth() const
{
	return HealthComp->GetHealth();
}

bool ABaseCharacter::IsDead() const
{
	return HealthComp->IsDead();
}