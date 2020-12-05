#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"

APlayerCharacter::APlayerCharacter() 
{
	PrimaryActorTick.bCanEverTick = true;

    PusherMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Pusher Mesh"));
    PusherMesh->SetupAttachment(RootComponent);

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

void APlayerCharacter::BeginPlay() 
{
    Super::BeginPlay();
    // Get a reference to this character's inherited skeletal mesh
    MainMesh = GetMesh();
    // Cache a reference to our player controller for later
    PlayerControllerRef = GetController<APlayerController>();
    if (PlayerControllerRef) 
    {
        PlayerControllerRef->bShowMouseCursor = true;
    }
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerCharacter::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);
    MoveForward();
    RotateTowardsMouse();
}

void APlayerCharacter::MoveForward() 
{
    FVector MoveDir = FVector(FVector::ForwardVector * MovementSpeed * GetWorld()->DeltaTimeSeconds);
    GetCharacterMovement()->AddInputVector(MoveDir);
}

void APlayerCharacter::RotateTowardsMouse() 
{
    if (PlayerControllerRef) 
    {
        // Raycast out from our mouse position into the world
        FHitResult HitResult;
        if (PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, false, HitResult))
        {
            // Rotate towards that position
            Rotate(HitResult.ImpactPoint);
        }
    }
}

void APlayerCharacter::Rotate(FVector LookAtTarget) 
{
    FVector StartLocation = MainMesh->GetComponentLocation();
    // LookAtTarget should be on the same Z as the actor
    FVector LookAtTargetClean = FVector(LookAtTarget.X, LookAtTarget.Y, StartLocation.Z);
    // Get the vector from StartLocation -> LookAtTarget
    FVector TargetVector = FVector(LookAtTargetClean - StartLocation);
    FVector Correction = FVector::CrossProduct(TargetVector, FVector::UpVector);
    FRotator Rotator = Correction.Rotation();
    // Set our rotation to match the above vector
    MainMesh->SetWorldRotation(Rotator);
}