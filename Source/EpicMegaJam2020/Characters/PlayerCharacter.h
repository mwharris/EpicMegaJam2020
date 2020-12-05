#pragma once

#include "CoreMinimal.h"
#include "EpicMegaJam2020/Characters/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

class AGun;
class UCameraComponent;
class USkeletalMeshComponent;
class USpringArmComponent;

UCLASS()
class EPICMEGAJAM2020_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* PusherMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AGun> GunClass;
	UPROPERTY()
	AGun* Gun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MovementSpeed = 100.f;

	class USkeletalMeshComponent* MainMesh;
	APlayerController* PlayerControllerRef;
	
	void MoveForward();
	void RotateTowardsMouse();
	void Rotate(FVector LookAtTarget);
	void SpawnGun();
	void Shoot();

};
