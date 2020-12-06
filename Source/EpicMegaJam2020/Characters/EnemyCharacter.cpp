#include "EnemyCharacter.h"
#include "AIController.h"
#include "Animation/AnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EpicMegaJam2020/Components/HealthComponent.h"
#include "EpicMegaJam2020/Characters/BaseCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

AEnemyCharacter::AEnemyCharacter() 
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEnemyCharacter::BeginPlay() 
{
    Super::BeginPlay();
    AIController = Cast<AAIController>(GetController());
    PlayerCharacter = Cast<ABaseCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    MeshComp = GetMesh();
}

void AEnemyCharacter::HandleDeath() 
{
    Super::HandleDeath();
    // Set a timer for our death
    GetWorldTimerManager().SetTimer(DeathTimerHandle, this, &AEnemyCharacter::DestroySelf, DestroyTime, false);
    // Stop moving once we've died
    if (AIController) 
    {
        AIController->StopMovement();
    }
    // Deactivate collisions
    GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AEnemyCharacter::DamagePlayer() 
{
    UGameplayStatics::ApplyDamage(PlayerCharacter, Damage, GetInstigatorController(), this, DamageType);
}

bool AEnemyCharacter::CanAttack() const
{
    return IsInAttackRange() && !IsAttacking() && !IsDead();
}

bool AEnemyCharacter::IsInAttackRange() const
{
    if (PlayerCharacter == nullptr) { return false; }
    return GetDistanceTo(PlayerCharacter) <= AttackRange;
}

bool AEnemyCharacter::IsAttacking() const
{
    return GetMesh()->GetAnimInstance()->Montage_IsPlaying(AttackMontage);
}

bool AEnemyCharacter::IsDead() const
{
    if (HealthComp == nullptr) { return false; }
    return HealthComp->IsDead();
}

void AEnemyCharacter::DestroySelf() 
{
    Destroy();
}