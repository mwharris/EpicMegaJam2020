#pragma once

#include "CoreMinimal.h"
#include "EpicMegaJam2020/Characters/BaseCharacter.h"
#include "EnemyCharacter.generated.h"

class AAIController;
class ABaseCharacter;
class UAnimMontage;
class USkeletalMeshComponent;

UCLASS()
class EPICMEGAJAM2020_API AEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void DamagePlayer();
	UFUNCTION(BlueprintCallable)
	bool CanAttack() const;

	AEnemyCharacter();
	virtual void HandleDeath() override;
	bool IsDead() const;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties", meta = (AllowPrivateAccess = "true"))
	float DestroyTime = 5.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	float AttackRange = 50.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	float Damage = 50.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	UAnimMontage* AttackMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UDamageType> DamageType;

	AAIController* AIController;
	ABaseCharacter* PlayerCharacter;
	USkeletalMeshComponent* MeshComp;
	FTimerHandle DeathTimerHandle;

	void DestroySelf();
	bool IsInAttackRange() const;
	bool IsAttacking() const;

};