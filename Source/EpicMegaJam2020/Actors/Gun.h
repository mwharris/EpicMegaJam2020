#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class EPICMEGAJAM2020_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	AGun();
	void Shoot(FVector& LookAtTarget);
	void Release();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USceneComponent* RootSceneComponent;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USkeletalMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, Category = "Properties")
	TSubclassOf<UDamageType> DamageType;
	UPROPERTY(EditAnywhere, Category = "Properties")
	float MaxRange = 5000.f;
	UPROPERTY(EditAnywhere, Category = "Properties")
	float Damage = 10.f;

	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* MuzzleFlash;
	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* HitEffect;
	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* ShotLoopSound;
	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* ShotEndSound;

	UParticleSystemComponent* MuzzleParticleComp;
	UAudioComponent* ShotAudioComp;

	bool GunTrace(FHitResult& OutHitResult, FVector& LookAtTarget);
	AController* GetOwnerController() const;

};