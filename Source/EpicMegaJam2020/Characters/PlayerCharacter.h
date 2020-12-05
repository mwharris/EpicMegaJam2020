#pragma once

#include "CoreMinimal.h"
#include "EpicMegaJam2020/Characters/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

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
	class USkeletalMeshComponent* PusherMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MovementSpeed = 100.f;

	class USkeletalMeshComponent* MainMesh;
	APlayerController* PlayerControllerRef;
	
	void MoveForward();
	void RotateTowardsMouse();
	void Rotate(FVector LookAtTarget);

};
