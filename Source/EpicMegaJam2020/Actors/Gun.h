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

	bool GunTrace(FHitResult& OutHitResult, FVector& LookAtTarget);
	AController* GetOwnerController() const;

};
